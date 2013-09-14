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
	- P_outside : pressure at the tip of the vessel outside the computational domain;

\*---------------------------------------------------------------------------*/
	#include "Vessels.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// CONSTRUCTOR

Vessels::Vessels
	(
		const double &xCoordinate, 
		const double &yCoordinate, 
		const double &zCoordinate, 
		const double &vesselLength, 
		const double &vesselRadius, 
		const double &P_outside
	)
	: 
		m_xCoordinate(xCoordinate), 
		m_yCoordinate(yCoordinate), 
		m_zCoordinate(zCoordinate), 
		m_vesselLength(vesselLength), 
		m_vesselRadius(vesselRadius), 
		m_P_outside(P_outside)
	{}


// METHODS 


// Calculation of corresponding index for point (xCoordinate,yCoordinate,zCoordinate) 


int Vessels::pointIndex(fvMesh &mesh) 

	{
		return mesh.findCell(point(m_xCoordinate,m_yCoordinate,m_zCoordinate));
	}

// Calculation of flow rate in the vessels


double Vessels::flowRate(fvMesh &mesh, IOdictionary &transportProperties, volScalarField &pPressure)

	{
	
		// Extracting viscosity and permeability values

		dimensionedScalar mu(transportProperties.lookup("mu"));
		dimensionedScalar K(transportProperties.lookup("K"));

		// Calculation of the blood flow rate according to Hagen-Poiseuille's law
	
		int index = pointIndex(mesh);
		double meshVolume = mesh.V()[index];
		double crossSectionalArea = M_PI*m_vesselRadius*m_vesselRadius;
		double pressureDifference = pPressure[index]-m_P_outside;
		double vesselResistance = 8.0*M_PI*mu.value()*m_vesselLength/(crossSectionalArea*crossSectionalArea);

		return pressureDifference/vesselResistance/meshVolume;
	}

// Application of the corrective well-model 


double Vessels::wellModel(fvMesh &mesh, IOdictionary &transportProperties, volScalarField &pPressure)

	{
		// Extracting viscosity and permeability values

		dimensionedScalar mu(transportProperties.lookup("mu"));
		dimensionedScalar K(transportProperties.lookup("K"));

		// Defining necessary variables for applying the well-model equation

		int index = pointIndex(mesh);
		double flow = flowRate(mesh, transportProperties, pPressure);
	    	double meshVolume = mesh.V()[index];
	    	double meshSize = Foam::pow(meshVolume,1.0/3.0);
		double equivalentRadius = 3.0*meshSize/(3.0+2.0*M_PI);

		// Applying the corrective model according to the well-model equation

		pPressure[index] += mu.value()*flow*meshVolume/(4.0*M_PI*K.value())*(1.0/equivalentRadius - 2.0/m_vesselRadius);

		return pPressure[index];
	}
