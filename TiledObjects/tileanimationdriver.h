/*-----------------------------------------------------------------------------------------------------------*/
#pragma once
/*-----------------------------------------------------------------------------------------------------------*/
#include <QAbstractAnimation>
#include "tiledobjects_global.h"
/*-----------------------------------------------------------------------------------------------------------*/
class TILEDOBJECTS_EXPORT TileAnimationDriver final : public QAbstractAnimation
{
	Q_OBJECT

public:
	explicit TileAnimationDriver(QObject* parent = nullptr);
	~TileAnimationDriver() override = default;

	TileAnimationDriver(const TileAnimationDriver&) = delete;
	TileAnimationDriver(TileAnimationDriver&&) = delete;

	TileAnimationDriver& operator=(const TileAnimationDriver&) = delete;
	TileAnimationDriver& operator=(TileAnimationDriver&&) = delete;

	int duration() const override;

signals:
	void update(int deltaTime);

protected:
	void updateCurrentTime(int currentTime) override;
	void updateState(State newState, State oldState) override;

private:
	int mLastTime;
};
/*-----------------------------------------------------------------------------------------------------------*/