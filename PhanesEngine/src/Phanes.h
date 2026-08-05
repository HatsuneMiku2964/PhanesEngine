#pragma once

// For the applications

// from the engine
#include "Phanes/Core/Input.h"
#include "Phanes/Core/Log/Log.h"
#include "Phanes/Core/Layer/Layer.h"
#include "Phanes/Core/App/Application.h"
#include "Phanes/Core/TimeStep/TimeStep.h"


// maths
#include <glm/glm/glm.hpp>

// rendering
#include "Phanes/Core/Renderer/Renderer/Renderer.h"
#include "Phanes/Core/Renderer/RenderCommand/RenderCommand.h"

#include "Phanes/Core/Renderer/Buffer/Buffer.h"
#include "Phanes/Core/Renderer/Shader/Shader.h"
#include "Phanes/Core/Renderer/Texture/Texture.h"
#include "Phanes/Core/Renderer/VertexArray/VertexArray.h"

#include "Phanes/Core/Renderer/Camera/OrthographicCamera.h"


// keycodes
#include "Phanes/Core/KeyCodes/KeyCodes.h"
#include "Phanes/Core/KeyCodes/MouseButtons.h"


// dependencies
#include "Phanes/ImGui/ImGuiLayer.h"


// the entry point ( int main() )
#include "Phanes/Core/Entry.h"