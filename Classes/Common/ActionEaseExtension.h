#pragma once

#include "CrazyIQ.h"

/**********************************************************************************************//**
 * @class	CCEaseCubicIn
 *
 * @brief	A Cc ease cubic in.
 *
 * @author	Huanchong
 * @date	11/24/2013
 **************************************************************************************************/

class CCEaseCubicIn :
	public CCActionEase
{
public:

	virtual CCObject* copyWithZone( CCZone* pZone );

	virtual void update( float time );

	virtual CCActionInterval* reverse( void );

};

/**********************************************************************************************//**
 * @class	CCEaseCubicOut
 *
 * @brief	A Cc ease cubic out.
 *
 * @author	Huanchong
 * @date	11/24/2013
 **************************************************************************************************/

class CCEaseCubicOut :
	public CCActionEase
{
public:

	virtual CCObject* copyWithZone( CCZone* pZone );

	virtual void update( float time );

	virtual CCActionInterval* reverse( void );

};

/**********************************************************************************************//**
 * @class	CCEaseCubicInOut
 *
 * @brief	A Cc ease cubic in out.
 *
 * @author	Huanchong
 * @date	11/24/2013
 **************************************************************************************************/

class CCEaseCubicInOut :
	public CCActionEase
{
public:

	virtual CCObject* copyWithZone( CCZone* pZone );

	virtual void update( float time );

	virtual CCActionInterval* reverse( void );

};