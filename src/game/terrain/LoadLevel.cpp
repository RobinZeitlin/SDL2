#include "LoadLevel.h"

void LoadLevel::save_level(const std::string& saveFile)
{
	int maxX = 0, maxY = 0;
	for (const auto& actor : currentLevel) {
		glm::vec2 pos = actor->transform.position;
		maxX = std::max(maxX, static_cast<int>(pos.x / 32.0f));
		maxY = std::max(maxY, static_cast<int>(pos.y / 32.0f));
	}

	// init empty grid
	std::vector<std::string> levelGrid(maxY + 1, std::string(maxX + 1, ' '));

	// populate grid
	for (const auto& actor : currentLevel) {
		glm::vec2 pos = actor->transform.position;
		int x = static_cast<int>(pos.x / 32.0f);
		int y = static_cast<int>(pos.y / 32.0f);

		char symbol;
		if (dynamic_cast<Block*>(actor)) symbol = 'D';
		else if (dynamic_cast<GrassBlock*>(actor)) symbol = 'G';
		else if (dynamic_cast<Stairs*>(actor)) symbol = 'S';
		else if (dynamic_cast<Enemy*>(actor)) symbol = 'E';
		else continue;

		if (y < levelGrid.size() && x < levelGrid[y].size()) {
			levelGrid[y][x] = symbol;
		}
	}

	levelGrid[0][0] = 'P';

	// save the grid to the file
	std::ofstream file(saveFile + ".csv");
	if (!file.is_open()) {
		Debug::log("File did not open correctly for saving.");
		return;
	}

	for (const auto& row : levelGrid) {
		file << row << '\n';
	}

	file.close();
	Debug::log("Level saved successfully.");
}

void LoadLevel::clear_current_level()
{
	if (currentLevel.size() == 0)
		return;

	for (auto actor : currentLevel)
	{
		actor->destroy();
		std::cout << "Destroyed" << std::endl;
	}

	currentLevel.clear();
}

void LoadLevel::place_actor(glm::vec2 atPos, Actor* actor)
{
	if (atPos.x < 0 || atPos.y < 0) return;

	glm::vec2 flooredPos = glm::vec2((int)(atPos.x / 32) * 32, (int)(atPos.y / 32) * 32);

	game->spawnActor(actor, flooredPos);

	currentLevel.push_back(actor);
}

void LoadLevel::destroy_actor(glm::vec2 atPos)
{
	glm::vec2 flooredPos = glm::vec2((int)(atPos.x / 32) * 32, (int)(atPos.y / 32) * 32);
	for (int i = 0; i < currentLevel.size(); i++)
	{
		auto actorInLevel = currentLevel[i];
		if (actorInLevel == nullptr) return;

		if (actorInLevel->transform.position == flooredPos)
		{
			actorInLevel->destroy();
			currentLevel.erase(currentLevel.begin() + i);
			break;
		}
	}
}

void LoadLevel::spawn_level(const std::vector<std::string>& data, bool bSpawnPlayer)
{
	bool shouldExit = false;

	for (int i = 0; i < data.size() && !shouldExit; ++i)
	{
		for (int j = 0; j < data[i].length() && !shouldExit; ++j)
		{
			glm::vec2 position(j * 32.0f, i * 32.0f);
			glm::vec2 scale(32.0f, 32.0f);
			Actor* actor = nullptr;

			switch (data[i][j]) {
			case 'D':
				actor = new Block();
				game->spawnActor(actor, position, scale);
				break;

			case 'G':
				actor = new GrassBlock();
				game->spawnActor(actor, position, scale);
				break;

			case 'S':
				actor = new Stairs();
				game->spawnActor(actor, position, scale);
				break;

			case 'E':
				actor = new Enemy();
				game->spawnActor(actor, position, scale);
				break;

			case 'P':
				if (bSpawnPlayer)
					game->spawnPlayer(position);
				break;

			case 'Q':
				shouldExit = true;
				break;

			default:
				break;
			}

			if (actor != nullptr)
				add_actor(actor);
		}
	}
}

void LoadLevel::load_level_file(string filePath, bool bSpawnPlayer)
{
	ifstream file(filePath + ".csv");
	if (!file.is_open()) {
		Debug::log("File did not open correctly.");
		return;
	}

	vector<string> data;
	string line;

	while (getline(file, line)) {
		data.push_back(line);
	}

	file.close();

	clear_current_level();
	spawn_level(data, bSpawnPlayer);
}
