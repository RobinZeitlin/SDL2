#pragma once

#include "Actor.h"

class LevelEditor;
class LoadLevel;

enum CurrentEditorTool {
	BuilderTool,
	BucketTool,
	SplineTool,
};

class CameraController : public Actor {
public:
	CameraController(LevelEditor* lvlEditor, LoadLevel* loadLvl) 
		: levelEditor(lvlEditor), loadLevel(loadLvl)
	{
		actorName = "Player";
        transform.position = glm::vec2(0);
	}

	CurrentEditorTool crtEditorTool = CurrentEditorTool::BuilderTool;
	LevelEditor* levelEditor;
	LoadLevel* loadLevel;

	void update(float dt);
};