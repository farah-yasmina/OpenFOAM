/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2011 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Vessels

Description
    Calculates blood flow & pressure distribution by applying a well model for arteries and veins.
	
Variables 
	- xCoordinate, yCoordinate, zCoordinate : cartesian coordinates (x,y,z)
	  of artery entrance or vein exit in the computational domain;
	- vesselLength : length of the vessel (artery or vein);
	- vesselRadius : mean (constant) radius of the vessel (artery or vein);
	- P_outside : pressure at the end of the vessel outside the computational
				  domain;
	- P_inside : pressure at the end of the vessel inside the computational domain.

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"

#ifndef Vessels_H
#define Vessels_H

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

class Vessels
{
	public:

		Vessels
		(
			const double &xCoordinate, 
			const double &yCoordinate, 
			const double &zCoordinate, 
			const double &vesselLength, 
			const double &vesselRadius, 
			const double &P_outside
		);


		int pointIndex(fvMesh &mesh);
		double flowRate(fvMesh &mesh, IOdictionary &transportProperties, volScalarField &pPressure);
		double wellModel(fvMesh &mesh, IOdictionary &transportProperties, volScalarField &pPressure);

	private:

		double m_xCoordinate; 
		double m_yCoordinate;
		double m_zCoordinate; 
		double m_vesselLength;
		double m_vesselRadius;
		double m_P_outside;
		
};

#endif
