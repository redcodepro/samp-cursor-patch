/*
	Plugin-SDK (Grand Theft Auto San Andreas) source file
	Authors: GTA Community. See more here
	https://github.com/DK22Pac/plugin-sdk
	Do not delete this comment block. Respect others' work!
*/
#include "CPad.h"

CMouseControllerState & CPad::PCTempMouseControllerState = *(CMouseControllerState *)0xB73404;
CMouseControllerState & CPad::NewMouseControllerState = *(CMouseControllerState *)0xB73418;
CMouseControllerState & CPad::OldMouseControllerState = *(CMouseControllerState *)0xB7342C;

CPad::CPad()
{
	((void(__thiscall*)(CPad*))(0x541D80))(this);
}

void CPad::UpdateMouse()
{
	((void(__thiscall*)(CPad*))(0x53F3C0))(this);
}

void CPad::ReconcileTwoControllersInput(CControllerState const& controllerA, CControllerState const& controllerB)
{
	((void(__thiscall*)(CPad*, CControllerState const&, CControllerState const&))(0x53F530))(this, controllerA, controllerB);
}

void CPad::SetDrunkInputDelay(int delay)
{
	((void(__thiscall*)(CPad*, int))(0x53F910))(this, delay);
}

void CPad::StartShake(short time, unsigned char frequency, unsigned int arg2)
{
	((void(__thiscall*)(CPad*, short, unsigned char, unsigned int))(0x53F920))(this, time, frequency, arg2);
}

void CPad::StartShake_Distance(short time, unsigned char frequency, float x, float y, float z)
{
	((void(__thiscall*)(CPad*, short, unsigned char, float, float, float))(0x53F9A0))(this, time, frequency, x, y, z);
}

void CPad::StartShake_Train(float x, float y)
{
	((void(__thiscall*)(CPad*, float, float))(0x53FA70))(this, x, y);
}

void CPad::ProcessPCSpecificStuff()
{
	((void(__thiscall*)(CPad*))(0x53FB40))(this);
}

void CPad::StopShaking(short arg0)
{
	((void(__thiscall*)(CPad*, short))(0x53FB50))(this, arg0);
}

CPad* CPad::GetPad(int padNumber)
{
	return ((CPad*(__cdecl*)(int))(0x53FB70))(padNumber);
}

short CPad::GetSteeringLeftRight()
{
	return ((short(__thiscall*)(CPad*))(0x53FB80))(this);
}

short CPad::GetSteeringUpDown()
{
	return ((short(__thiscall*)(CPad*))(0x53FBD0))(this);
}

short CPad::GetPedWalkLeftRight()
{
	return ((short(__thiscall*)(CPad*))(0x53FC90))(this);
}

short CPad::GetPedWalkUpDown()
{
	return ((short(__thiscall*)(CPad*))(0x53FD30))(this);
}

bool CPad::GetLookLeft()
{
	return ((bool(__thiscall*)(CPad*))(0x53FDD0))(this);
}

bool CPad::GetLookRight()
{
	return ((bool(__thiscall*)(CPad*))(0x53FE10))(this);
}

bool CPad::GetLookBehindForCar()
{
	return ((bool(__thiscall*)(CPad*))(0x53FE70))(this);
}

bool CPad::GetLookBehindForPed()
{
	return ((bool(__thiscall*)(CPad*))(0x53FEC0))(this);
}

bool CPad::GetHorn()
{
	return ((bool(__thiscall*)(CPad*))(0x53FEE0))(this);
}

bool CPad::HornJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x53FF30))(this);
}

bool CPad::GetHydraulicJump()
{
	return ((bool(__thiscall*)(CPad*))(0x53FF70))(this);
}

short CPad::GetCarGunFired()
{
	return ((short(__thiscall*)(CPad*))(0x53FF90))(this);
}

short CPad::CarGunJustDown()
{
	return ((short(__thiscall*)(CPad*))(0x53FFE0))(this);
}

short CPad::GetHandBrake()
{
	return ((short(__thiscall*)(CPad*))(0x540040))(this);
}

short CPad::GetBrake()
{
	return ((short(__thiscall*)(CPad*))(0x540080))(this);
}

bool CPad::GetExitVehicle()
{
	return ((bool(__thiscall*)(CPad*))(0x5400D0))(this);
}

bool CPad::ExitVehicleJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540120))(this);
}

unsigned char CPad::GetMeleeAttack()
{
	return ((unsigned char(__thiscall*)(CPad*))(0x540340))(this);
}

unsigned char CPad::MeleeAttackJustDown()
{
	return ((unsigned char(__thiscall*)(CPad*))(0x540390))(this);
}

short CPad::GetAccelerate()
{
	return ((short(__thiscall*)(CPad*))(0x5403F0))(this);
}

bool CPad::GetAccelerateJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540440))(this);
}

bool CPad::NextStationJustUp()
{
	return ((bool(__thiscall*)(CPad*))(0x5405B0))(this);
}

bool CPad::LastStationJustUp()
{
	return ((bool(__thiscall*)(CPad*))(0x5405E0))(this);
}

bool CPad::CycleWeaponLeftJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540610))(this);
}

bool CPad::CycleWeaponRightJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540640))(this);
}

bool CPad::GetTarget()
{
	return ((bool(__thiscall*)(CPad*))(0x540670))(this);
}

bool CPad::GetDuck()
{
	return ((bool(__thiscall*)(CPad*))(0x540700))(this);
}

bool CPad::DuckJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540720))(this);
}

bool CPad::GetJump()
{
	return ((bool(__thiscall*)(CPad*))(0x540750))(this);
}

bool CPad::JumpJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540770))(this);
}

bool CPad::GetSprint()
{
	return ((bool(__thiscall*)(CPad*))(0x5407A0))(this);
}

bool CPad::SprintJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x5407F0))(this);
}

bool CPad::ShiftTargetLeftJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540850))(this);
}

bool CPad::ShiftTargetRightJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540880))(this);
}

short CPad::GetDisplayVitalStats(CPed* ped)
{
	return ((short(__thiscall *)(CPad*, CPed*))(0x5408B0))(this, ped);
}

bool CPad::CollectPickupJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x540A70))(this);
}

bool CPad::GetForceCameraBehindPlayer()
{
	return ((bool(__thiscall*)(CPad*))(0x540AE0))(this);
}

bool CPad::SniperZoomIn()
{
	return ((bool(__thiscall*)(CPad*))(0x540B30))(this);
}

bool CPad::SniperZoomOut()
{
	return ((bool(__thiscall*)(CPad*))(0x540B80))(this);
}

bool CPad::GetGroupControlForward()
{
	return ((bool(__thiscall*)(CPad*))(0x541190))(this);
}

bool CPad::GetGroupControlBack()
{
	return ((bool(__thiscall*)(CPad*))(0x5411B0))(this);
}

bool CPad::ConversationYesJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x5411D0))(this);
}

bool CPad::ConversationNoJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x541200))(this);
}

bool CPad::GroupControlForwardJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x541230))(this);
}

bool CPad::GroupControlBackJustDown()
{
	return ((bool(__thiscall*)(CPad*))(0x541260))(this);
}

void CPad::Clear(bool enablePlayerControls, bool resetPhase)
{
	((void(__thiscall *)(CPad*, bool, bool))(0x541A70))(this, enablePlayerControls, resetPhase);
}

void CPad::UpdatePads()
{
	((void(__cdecl *)(void))(0x541DD0))();
}

void CPad::ClearMouseHistory()
{
	((void(__cdecl *)(void))(0x541BD0))();
}