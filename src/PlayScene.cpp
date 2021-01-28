#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

PlayScene::PlayScene()
{
	PlayScene::start();

	SoundManager::Instance().load("../Assets/audio/maintrack.mp3", "main", SOUND_MUSIC);
	SoundManager::Instance().playMusic("main", 0);
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 0, 255, 255, 255); // temp turquoise background
}

void PlayScene::update()
{
	updateDisplayList();

	CollisionManager::AABBCheck(m_pUfo, m_pObstacle); //checks to see if collision
}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		//seek
		m_pUfo->setDestination(m_pTarget->getTransform()->position);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		//flee
		m_pUfo->getTransform()->position = glm::vec2(200.0f, 200.0f);
		m_pTarget->getTransform()->position = glm::vec2(200.0f, 150.0f);
		m_pUfo->setDestination(m_pTarget->getTransform()->position - m_pUfo->getTransform()->position);
		
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		//arrive
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_4))
	{
		//avoid obstacle
		addChild(m_pObstacle);
	}
}

void PlayScene::start()
{
	//m_pBackground = new Background();
	//m_pBackground->getTransform()->position = glm::vec2(400.0f, 300.0f);
	//addChild(m_pBackground, 1);

	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = glm::vec2(400.0f, 300.0f);
	addChild(m_pTarget);

	m_pObstacle = new Obstacle();
	m_pObstacle->getTransform()->position = glm::vec2(500.0f, 300.0f);
	//addChild(m_pObstacle);

	// instantiating spaceship
	m_pUfo = new Ufo();
	m_pUfo->getTransform()->position = glm::vec2(100.0f, 300.0f);
	m_pUfo->setEnabled(false);
	//m_pUfo->setDestination(m_pTarget->getTransform()->position);
	addChild(m_pUfo); 

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(300.0f, 400.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	//addChild(m_pBackButton);

	// Next Button
	m_pNextButton = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pNextButton->getTransform()->position = glm::vec2(500.0f, 400.0f);
	m_pNextButton->addEventListener(CLICK, [&]()-> void
	{
		m_pNextButton->setActive(false);
		TheGame::Instance()->changeSceneState(END_SCENE);
	});

	m_pNextButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pNextButton->setAlpha(128);
	});

	m_pNextButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pNextButton->setAlpha(255);
	});

	//addChild(m_pNextButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press 1-> Seeking/ 2-> Fleeing/ 3-> Arrival/ 4-> Obstacle Avoidance", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);

	addChild(m_pInstructionsLabel, 2);
}

void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	

	ImGui::Begin("GAME 3001 - A1", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	static float speed = 10.0f;
	if (ImGui::SliderFloat("MaxSpeed", &speed, 0.0f, 100.0f))
	{
		m_pUfo->setMaxSpeed(speed);

	}

	static float acceleration_rate = 2.0f;
	if (ImGui::SliderFloat("Acceleration Rate", &acceleration_rate, 0.0f, 50.0f))
	{
		m_pUfo->setAccelerationRate(acceleration_rate);
	}

	static float angleInRadians = 0.0f;
	if (ImGui::SliderAngle("Orientation Angle", &angleInRadians))
	{
		m_pUfo->setRotation(angleInRadians * Util::Rad2Deg);
	}

	static float turn_rate = 5.0f;
	if (ImGui::SliderFloat("Turn Rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pUfo->setTurnRate(turn_rate);
	}

	if(ImGui::Button("Start"))
	{
		m_pUfo->setEnabled(true);
	}

	ImGui::SameLine();

	if (ImGui::Button("Reset"))
	{
		m_pUfo->getTransform()->position = glm::vec2(200.0f, 200.0f);
		m_pUfo->setEnabled(false);
		m_pUfo->getRigidBody()->velocity = glm::vec2(0.0f); //reset velocity
		m_pUfo->setRotation(0.0f); //reset angle
		turn_rate = 5.0f;
		acceleration_rate = 2.0f;
		speed = 10.0f;
		angleInRadians = m_pUfo->getRotation();
	}

	ImGui::Separator();

	static float targetPosition[2] = { m_pTarget->getTransform()->position.x, m_pTarget->getTransform()->position.y };
	if (ImGui::SliderFloat2("Target", targetPosition, 0.0f, 800.0f))
	{
		m_pTarget->getTransform()->position = glm::vec2(targetPosition[0], targetPosition[1]);
		m_pUfo->setDestination(m_pTarget->getTransform()->position);
	}
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}
