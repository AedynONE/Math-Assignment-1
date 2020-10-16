#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "BackEnd.h"

//#define TOPDOWN


enum AnimEnums
{
	IDLELEFT,
	IDLERIGHT,
	
	CROUCHLEFT,
	CROUCHRIGHT,

	WALKLEFT,
	WALKRIGHT,
	
	JUMPLEFT,
	JUMPRIGHT,

	EXPLODE
};

enum AnimTypes
{
	IDLE = 0,
	CROUCH = 2,
	WALK = 4,
	JUMP = 6,
	DEATH = 8
};

enum AnimDir
{
	LEFT,
	RIGHT
};

class Player
{
public:
	Player();
	Player(std::string& fileName, std::string& animationJSON, int width, int height,
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = true, PhysicsBody* body = nullptr);

	void InitPlayer(std::string& fileName, std::string& animationJSON, int width, int height,
		Sprite* sprite, AnimationController* controller, Transform* transform, bool hasPhys = true, PhysicsBody* body = nullptr);

	void Update();
	void MovementUpdate();
	void AnimationUpdate();
	void SetSprite(Sprite* SprtCom){
		m_sprite = SprtCom;
	}

private:
	void SetActiveAnimation(int anim);

	//Basically, any animation OTHER than moving will not have a cancel, and we'll be checking whether or not that animation is done
	bool m_moving = false;
	//Are you currently attacking?????
	bool m_attacking = false;
	//Have we locked the player from moving during this animation?
	bool m_locked = false;

	//A reference to our sprite
	Sprite* m_sprite = nullptr;
	//A reference to our animation controller
	AnimationController* m_animController = nullptr;
	//A reference to our player transform
	Transform* m_transform = nullptr;

	//Physics importance
	//A reference to our physics body
	PhysicsBody* m_physBody = nullptr;
	//Does this player have physics?
	bool m_hasPhysics = true;

	//Default animation direction (feel free to change this to suit your game. If you're making a side-scroller, left or right would be better
	enum AnimDir m_facing = RIGHT;
};

#endif // !__PLAYER_H__