#include "BulletPattern01.h"
#include "Scenes/GameScene.h"

BulletPattern01* BulletPattern01::createBulletPattern(cocos2d::Vec2 origin, Player* player)
{
	BulletPattern01* ret = BulletPattern01::create();
	if (!ret)
	{
		CC_SAFE_DELETE(ret);
		return NULL;
	}
	ret->origin = origin;
	ret->player = player;
	ret->hp = ret->PATTERN_HP;
	
	ret->createLasers();
	ret->calcRandomMentosMinMaxValues();

	ret->laserRotation = 180.0f;
	ret->arrowheadRotation = ret->ARROWHEAD_ANGLE_MIN;
	ret->mentosRotation = ret->MENTOS_ANGLE_MIN;

	return ret;
}

void BulletPattern01::createLasers()
{
	for (cocos2d::Vec2 spawnPoint : ARROWHEAD_SPAWN_POINTS)
	{
		lasers.push_back(Laser::createLaser(spawnPoint, 0.0f));
		addChild(lasers.back());
	}
}

void BulletPattern01::calcRandomMentosMinMaxValues()
{
	randomMentosMaxX = GameScene::GAME_INNER_BOUNDS[2].x - 20;
	randomMentosMinX = GameScene::GAME_INNER_BOUNDS[0].x + 20;
	randomMentosMaxY = GameScene::GAME_INNER_BOUNDS[2].y - 20;
	randomMentosMinY = randomMentosMaxY - 150;
}

void BulletPattern01::update(float delta)
{
	arrowheadRotation += arrowheadRotationSpeed * delta;
	if (arrowheadRotation >= ARROWHEAD_ANGLE_MAX || arrowheadRotation <= ARROWHEAD_ANGLE_MIN)
	{
		arrowheadRotationSpeed *= -1.0f;
	}

	laserRotation += laserRotationSpeed * delta;
	if (laserRotation >= LASER_ANGLE_MAX || laserRotation <= LASER_ANGLE_MIN)
	{
		laserRotationSpeed *= -1.0f;
	}

	for (Laser* laser : lasers)
	{
		laser->setRotation(laserRotation);
		laserRotation = 180.0f + (180.0f - laserRotation);
	}

	spawnBubbles(delta);
	spawnMentos(delta);
	spawnBounceMentos(delta);
	spawnRandomMentos(delta);
	spawnArrowheads(delta);

	updateBullets(delta);

	for (Bullet* bullet : bullets)
	{
		if (bullet->getType() == Bullet::MENTOS && bullet->getSubtype() == 1 && bullet->isOutOfInnerBounds())
		{
			bullet->setSubtype(2);
			bullet->setSpeed(BOUNCE_MENTOS_SPEED);
			bullet->aimAt(player->getPos());
		}
	}

}

void BulletPattern01::spawnBubbles(float delta)
{
	if (nextBubbleInterval > 0.0f)
	{
		nextBubbleInterval -= delta;
		return;
	}

	nextBubbleInterval += BUBBLE_SPAWN_INTERVAL;

	for (int i = 0; i < 3; i++)
	{
		bullets.push_back(Bullet::createBullet(origin, Bullet::BUBBLE));
		bullets.back()->setSpeed(MENTOS_SPEED);
		bullets.back()->aimAt(player->getPos(), (i - 1) * BUBBLE_ANGLE_DIFF);
		addChild(bullets.back());
	}
}

void BulletPattern01::spawnMentos(float delta)
{
	if (nextMentosInterval > 0.0f)
	{
		nextMentosInterval -= delta;
		return;
	}
	
	nextMentosInterval += MENTOS_SPAWN_INTERVAL;
	
	mentosRotation += mentosRotationSpeed;
	if (mentosRotation >= MENTOS_ANGLE_MAX || mentosRotation <= MENTOS_ANGLE_MIN)
	{
		mentosRotationSpeed *= -1.0f;
	}

	bullets.push_back(Bullet::createBullet(origin, Bullet::MENTOS));
	bullets.back()->setSpeed(MENTOS_SPEED);
	bullets.back()->setRot(mentosRotation);
	addChild(bullets.back());
}

void BulletPattern01::spawnBounceMentos(float delta)
{
	bounceMentosRotation += bounceMentosRotationSpeed * delta;
	if (bounceMentosRotation >= 180.0f || bounceMentosRotation <= -180.0f)
	{
		bounceMentosRotationSpeed *= -1.0f;
	}

	if (nextBounceMentosInterval > 0.0f)
	{
		nextBounceMentosInterval -= delta;
		return;
	}

	nextBounceMentosInterval += BOUNCE_MENTOS_SPAWN_INTERVAL;

	if (bounceMentosRotation <= BOUNCE_MENTOS_ANGLE_MAX &&
		bounceMentosRotation >= BOUNCE_MENTOS_ANGLE_MIN)
	{
		bullets.push_back(Bullet::createBullet(origin, Bullet::MENTOS, 1));
		bullets.back()->setSpeed(MENTOS_SPEED);
		bullets.back()->setRot(bounceMentosRotation);
		addChild(bullets.back());
	}
}

void BulletPattern01::spawnRandomMentos(float delta)
{
	if (nextRandomMentosInterval > 0.0f)
	{
		nextRandomMentosInterval -= delta;
		return;
	}

	nextRandomMentosInterval += RANDOM_MENTOS_SPAWN_INTERVAL;

	for (int i = 0; i < RANDOM_MENTOS_IN_BATCH; i++)
	{
		float x = (float)std::rand() / (float)RAND_MAX * (randomMentosMaxX - randomMentosMinX) + randomMentosMinX;
		float y = (float)std::rand() / (float)RAND_MAX * (randomMentosMaxY - randomMentosMinY) + randomMentosMinY;

		float angle = (float)std::rand() / (float)RAND_MAX * RANDOM_MENTOS_ANGLE_VARIATION;
		angle += RANDOM_MENTOS_BASE_ANGLE;

		bullets.push_back(Bullet::createBullet(cocos2d::Vec2(x, y), Bullet::MENTOS));
		bullets.back()->setSpeed(MENTOS_SPEED);
		bullets.back()->setRot(angle);
		addChild(bullets.back());
	}
}

void BulletPattern01::spawnArrowheads(float delta)
{
	if (nextArrowheadInterval > 0.0f)
	{
		nextArrowheadInterval -= delta;
		return;
	}

	nextArrowheadInterval += ARROWHEAD_SPAWN_INTERVAL;

	for (cocos2d::Vec2 spawnPoint : ARROWHEAD_SPAWN_POINTS)
	{
		for (int i = 0; i < 3; i++)
		{
			bullets.push_back(Bullet::createBullet(spawnPoint, Bullet::ARROWHEAD));
			bullets.back()->setSpeed(ARROWHEAD_SPEED);
			bullets.back()->setRot(arrowheadRotation + (i - 1) * ARROWHEAD_ANGLE_BETWEEN_ARMS);
			addChild(bullets.back());
		}
		arrowheadRotation = 180.0f + (180.0f - arrowheadRotation);
	}
}
