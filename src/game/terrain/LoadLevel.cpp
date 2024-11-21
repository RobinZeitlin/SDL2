#include "LoadLevel.h"
#include <queue>
#include <algorithm>

void LoadLevel::save_level(const std::string& saveFile)
{
    int maxX = actorGrid.size();
    int maxY = maxX > 0 ? actorGrid[0].size() : 0;

    std::vector<std::string> levelGrid(maxY, std::string(maxX, ' '));

    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            if (actorGrid[x][y]) {
                if (dynamic_cast<GrassBlock*>(actorGrid[x][y])) levelGrid[y][x] = 'G';
                else if (dynamic_cast<Stairs*>(actorGrid[x][y])) levelGrid[y][x] = 'S';
                else if (dynamic_cast<Enemy*>(actorGrid[x][y])) levelGrid[y][x] = 'E';
                else if (dynamic_cast<SpawnPoint*>(actorGrid[x][y])) levelGrid[y][x] = 'P';
                else if (dynamic_cast<Block*>(actorGrid[x][y])) levelGrid[y][x] = 'D';
            }
        }
    }

    std::ofstream file(saveFile + ".csv");
    if (!file.is_open()) {
        Debug::log("File did not open correctly for saving.");
        return;
    }

    for (const auto& row : levelGrid) {
        file << row << '\n';
    }

    file << "---SPLINES---\n";

    for (const auto& splinePoint : game->spline->splinePoints) {
        file << splinePoint->transform.position.x << ","
            << splinePoint->transform.position.y << ","
            << splinePoint->transform.rotation.x << ","
            << splinePoint->transform.rotation.y << ","
            << splinePoint->handles->distance << '\n';
    }

    file.close();
    Debug::log("Level saved successfully.");
}

void LoadLevel::clear_current_level()
{
    for (auto& row : actorGrid) {
        for (auto& actor : row) {
            if (actor) {
                actor->destroy();
                actor = nullptr;
            }
        }
    }
    std::cout << "Cleared Grid" << std::endl;
}

void LoadLevel::place_actor(glm::vec2 atPos, Actor* actor)
{
    int x = static_cast<int>(atPos.x / 32);
    int y = static_cast<int>(atPos.y / 32);

    if (x >= 0 && y >= 0 && x < actorGrid.size() && y < actorGrid[0].size()) {
        if (actorGrid[x][y] == nullptr) {
            game->spawnActor(actor, glm::vec2(x * 32, y * 32));
            actorGrid[x][y] = actor;
        }
    }
}

void LoadLevel::add_actor(glm::vec2 gridPos, Actor* actor)
{
    int x = static_cast<int>(gridPos.x);
    int y = static_cast<int>(gridPos.y);

    if (y >= actorGrid.size()) {
        actorGrid.resize(y + 1);
    }
    if (x >= actorGrid[y].size()) {
        actorGrid[y].resize(x + 1, nullptr);
    }

    actorGrid[y][x] = actor;
}

void LoadLevel::fill_tool(glm::vec2 clickedPos) {
    int currentX = clickedPos.x / 32;
    int currentY = clickedPos.y / 32;

    if (currentX < 0 || currentX >= actorGrid.size() ||
        currentY < 0 || currentY >= actorGrid[0].size()) {
        return;
    }

    std::queue<glm::vec2> queue;
    queue.push({ currentX, currentY });

    std::vector<std::vector<bool>> visited(actorGrid.size(), std::vector<bool>(actorGrid[0].size(), false));
    visited[currentX][currentY] = true;

    std::vector<glm::vec2> directions = { 
        {1, 0}, 
        {0, 1}, 
        {-1, 0}, 
        {0, -1} 
    };

    while (!queue.empty()) {
        glm::vec2 pos = queue.front();
        queue.pop();

        game->levelEditor->place_actor({ pos.x * 32, pos.y * 32 });

        for (const auto& dir : directions) {
            int newX = pos.x + dir.x;
            int newY = pos.y + dir.y;

            if (newX >= 0 && newY >= 0 && newX < actorGrid.size() && newY < actorGrid[0].size()) {
                if (!visited[newX][newY] && actorGrid[newX][newY] == nullptr) {
                    queue.push({ newX, newY });
                    visited[newX][newY] = true;
                }
            }
        }
    }
}

void LoadLevel::destroy_actor(glm::vec2 atPos)
{
    int x = static_cast<int>(atPos.x / 32);
    int y = static_cast<int>(atPos.y / 32);

    if (x >= 0 && y >= 0 && x < actorGrid.size() && y < actorGrid[0].size()) {
        if (actorGrid[x][y]) {
            actorGrid[x][y]->destroy();
            actorGrid[x][y] = nullptr;
        }
    }
}

void LoadLevel::spawn_level(const std::vector<std::string>& data, bool bSpawnPlayer)
{
    int maxX = data[0].size();
    int maxY = data.size();
    actorGrid.resize(maxX, std::vector<Actor*>(maxY, nullptr));

    for (int y = 0; y < maxY; ++y) {
        for (int x = 0; x < maxX; ++x) {
            glm::vec2 position(x * 32.0f, y * 32.0f);
            glm::vec2 scale(32.0f, 32.0f);
            Actor* actor = nullptr;

            switch (data[y][x]) {
            case 'D':
                actor = new Block();
                break;
            case 'G':
                actor = new GrassBlock();
                break;
            case 'S':
                actor = new Stairs();
                break;
            case 'E':
                actor = new Enemy();
                break;
            case 'P':
                if (bSpawnPlayer) {
                    game->spawnPlayer(position);
                }
                break;
            case 'Q':
                return;
            default:
                break;
            }

            if (actor != nullptr) {
                game->spawnActor(actor, position, scale);
                actorGrid[x][y] = actor;
            }
        }
    }
}

void LoadLevel::load_level_file(string filePath, bool bSpawnPlayer)
{
    lastLevelWithPath = filePath;

    if (!game->spline->splinePoints.empty()) game->spline->clear_spline_points();

    std::ifstream file(filePath + ".csv");
    if (!file.is_open()) {
        Debug::log("File did not open correctly.");
        return;
    }

    std::vector<std::string> data;
    std::string line;

    bool readingGrid = true;
    while (std::getline(file, line)) {
        if (line == "---SPLINES---") {
            readingGrid = false;
            continue;
        }

        if (readingGrid) {
            data.push_back(line);
        }
        else {
            std::istringstream stream(line);
            float px, py, rx, ry, d;
            char comma;

            if (stream >> px >> comma >> py >> comma >> rx >> comma >> ry >> comma >> d) {
                SplinePoint* splinePoint = new SplinePoint();
                splinePoint->transform.position = glm::vec2(px, py);
                splinePoint->transform.rotation = glm::vec2(rx, ry);
                splinePoint->handles->distance = d;
                game->spline->splinePoints.push_back(splinePoint);
            }
        }
    }

    file.close();

    clear_current_level();
    spawn_level(data, bSpawnPlayer);
}

bool LoadLevel::is_walkable(glm::vec2 posInGrid)
{
    int x = static_cast<int>(posInGrid.x);
    int y = static_cast<int>(posInGrid.y);

    if (actorGrid.empty()) return true;

    if (x < 0 || x >= actorGrid.size() || y < 0 || y >= actorGrid[x].size()) {
        return false;
    }

    if (actorGrid[x][y] != nullptr) {
        return false;
    }

    return true;
}