#pragma once

// For the applications

// from the engine
#include "Phanes/Input.h"
#include "Phanes/Log/Log.h"
#include "Phanes/Layer/Layer.h"
#include "Phanes/App/Application.h"
#include "Phanes/Core/TimeStep/TimeStep.h"


// maths
#include <glm/glm/glm.hpp>

// rendering
#include "Phanes/Renderer/Renderer/Renderer.h"
#include "Phanes/Renderer/RenderCommand/RenderCommand.h"

#include "Phanes/Renderer/Buffer/Buffer.h"
#include "Phanes/Renderer/Shader/Shader.h"
#include "Phanes/Renderer/VertexArray/VertexArray.h"

#include "Phanes/Renderer/Camera/OrthographicCamera.h"


// keycodes
#include "Phanes/KeyCodes/KeyCodes.h"
#include "Phanes/KeyCodes/MouseButtons.h"


// dependencies
#include "Phanes/ImGui/ImGuiLayer.h"


// the entry point ( int main() )
#include "Phanes/Entry.h"