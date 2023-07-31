#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
class SpaceGame : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};

public:
	SpaceGame() = default;

	// Inherited via Game
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void setState(eState p_state) { state = p_state; };
private:
	eState state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	float m_gameTimer = 0;
	float m_stateTimer = 0;

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_titleText;
	std::unique_ptr<kiko::Text> m_gameoverText;
	std::unique_ptr<kiko::Text> m_gameTimerText;
	std::unique_ptr<kiko::Text> m_retryText;
	std::unique_ptr<kiko::Text> m_startText;
	std::unique_ptr<kiko::Text> m_healthText;
	std::unique_ptr<kiko::Text> m_timeSurvived;
};