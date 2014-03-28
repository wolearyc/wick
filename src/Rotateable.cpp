// ----------------------------------------------------------------------------
// wick - a simple, object-oriented 2D game engine for Mac OSX written in C++
// Copyright (C) 2013-2014  Will O'Leary
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
// more details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------
// File:    Rotateable.cpp
// ----------------------------------------------------------------------------
#include "Rotateable.h"
namespace wick
{
    Rotateable::Rotateable(double rotation)
    :rotation_(rotation)
    {
    }
    Rotateable::Rotateable()
    :Rotateable(0.0)
    {
    }
    Rotateable::Rotateable(const Rotateable& other)
    :Rotateable(other.rotation_)
    {
    }
    double Rotateable::getRotation()
    {
        return(rotation_);
    }
    void Rotateable::setRotation(double rotation)
    {
        rotation_ = rotation;
    }
    void Rotateable::rotate(double rotation)
    {
        setRotation(rotation_ + rotation);
    }
}
