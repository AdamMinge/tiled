/*-----------------------------------------------------------------------------------------------------------*/
#include "tileanimationdriver.h"
/*-----------------------------------------------------------------------------------------------------------*/
TileAnimationDriver::TileAnimationDriver(QObject* parent) :
	QAbstractAnimation(parent),
	mLastTime(0)
{
	setLoopCount(-1);
}
/*-----------------------------------------------------------------------------------------------------------*/
int TileAnimationDriver::duration() const
{
	return 1000;
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileAnimationDriver::updateCurrentTime(int currentTime)
{
	auto elapsed = currentTime - mLastTime;

	if (elapsed < 0)
		elapsed += duration();

	mLastTime = currentTime;

	emit update(elapsed);
}
/*-----------------------------------------------------------------------------------------------------------*/
void TileAnimationDriver::updateState(State newState, State oldState)
{
	Q_UNUSED(oldState);

	if (newState == State::Stopped)
		mLastTime = 0;
}
/*-----------------------------------------------------------------------------------------------------------*/