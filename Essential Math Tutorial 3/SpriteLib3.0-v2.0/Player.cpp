#include "Player.h"
#include "JellyPlatforms.h"

Player::Player()
{
}

Player::Player(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, 
					AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	InitPlayer(fileName, animationJSON, width, height, sprite, controller, transform, hasPhys, body);
}

void Player::InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height, Sprite* sprite, 
							AnimationController* controller, Transform* transform, bool hasPhys, PhysicsBody* body)
{
	//store references to the components
	m_sprite = sprite;
	m_animController = controller;
	m_transform = transform;
	m_hasPhysics = hasPhys;
	if (hasPhys)
	{
		m_physBody = body;
	}

	//initialize UVs
	m_animController->InitUVs(fileName);

	//loads the texture and sets width and height
	m_sprite->LoadSprite(fileName, width, height, true, m_animController);
	m_animController->SetVAO(m_sprite->GetVAO());
	m_animController->SetTextureSize(m_sprite->GetTextureSize());

	//loads in the animations json file
	nlohmann::json animations = File::LoadJSON(animationJSON);

	/*for (int i = 0, i < animationNames.size(), i++)
	{
		m_animController->AddAnimation(animations[animationNames[i]].get<Animation>());
	}*/

	//IDLE ANIMATIONS\\
	
	//IdleLeft
	m_animController->AddAnimation(animations["IdleLeft"].get<Animation>());
	//IdleRight
	m_animController->AddAnimation(animations["IdleRight"].get<Animation>());
	//CrouchLeft
	m_animController->AddAnimation(animations["CrouchLeft"].get<Animation>());
	//CrouchRight
	m_animController->AddAnimation(animations["CrouchRight"].get<Animation>());

	//WALK ANIMATIONS\\

	//WalkLeft
	m_animController->AddAnimation(animations["MoveLeft"].get<Animation>());
	//WalkRight
	m_animController->AddAnimation(animations["MoveRight"].get<Animation>());

	//JUMP ANIMATIONS\\

	//jumpLeft
	m_animController->AddAnimation(animations["JumpLeft"].get<Animation>());
	//jumpRight
	m_animController->AddAnimation(animations["JumpRight"].get<Animation>());

	//DEATH\\

	//death
	m_animController->AddAnimation(animations["Explode"].get<Animation>());
	m_animController->AddAnimation(animations["Explode"].get<Animation>());


	//set default animation
		m_animController->SetActiveAnim(IDLERIGHT);
}

void Player::Update()
{
	if (!m_locked && !JellyPlatforms::dead)
	{
		MovementUpdate();
	}

	//if (!JellyPlatforms::dead) {
		AnimationUpdate();
	//}
}

void Player::MovementUpdate()
{
	m_moving = false;

	if (m_hasPhysics && !JellyPlatforms::dead)
	{

		if (Input::GetKey(Key::A))
		{
			//vel.x += -1.f;
			//vel = vel + vec3(-1.f, 0.f, 0.f);
			m_facing = LEFT;
			m_moving = true;
		}
		if (Input::GetKey(Key::D))
		{
			//vel.x += 1.f;
			//vel = vel + vec3(1.f, 0.f, 0.f);
			m_facing = RIGHT;
			m_moving = true;
		}
	}
}

void Player::AnimationUpdate()
{
	int activeAnimation = 0;

	if (JellyPlatforms::dead)
	{
		activeAnimation = EXPLODE;
		std::cout << "lol, you died\n\n\n";
		
	}
	if (!JellyPlatforms::dead)
	{
	if (m_moving)
	{
		//puts it into WALK category
		activeAnimation = WALK;
	}
	/*else if (m_attacking) {

		//check if attack animation is done
		if (m_animController->GetAnimation(m_animController->GetActiveAnim()).GetAnimationDone())
		{
			//will auto set to IDLE
			m_locked = false;
			m_attacking = false;
			//resets the attack animation
			m_animController->GetAnimation(m_animController->GetActiveAnim()).Reset();

			activeAnimation = IDLE;
		}
	}
	else
	{
		activeAnimation = IDLE;
	}*/

	if (Input::GetKey(Key::W))
	{
		m_moving = false;
		//SetActiveAnimation(IDLEDOWN);
		//if (m_facing == LEFT) {
		activeAnimation = JUMP;
		//}
	}

	if (Input::GetKey(Key::S))
	{
		m_moving = false;
		//SetActiveAnimation(IDLEDOWN);
		//if (m_facing == LEFT) {
		activeAnimation = CROUCH;
		//}
	}

	if (!JellyPlatforms::onGround) {
		activeAnimation = JUMP;
	}
}

		SetActiveAnimation(activeAnimation + (int)m_facing);

}
void Player::SetActiveAnimation(int anim)
{
	m_animController->SetActiveAnim(anim);
}
