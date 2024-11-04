#pragma once

#include "Actor.h"

enum CurrentEditorTool {
	BuilderTool,
	BucketTool,
	SplineTool,
};

class CameraController : public Actor {
public:
	CameraController()
	{
		actorName = "Player";
        transform.position = glm::vec2(0);
	}

	CurrentEditorTool crtEditorTool = CurrentEditorTool::BuilderTool;

	void update(float dt);
};