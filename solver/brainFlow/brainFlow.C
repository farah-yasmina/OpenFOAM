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

Application
    brainFlow

Description
    Calculates blood pressure and flow in a cerebral vascular network.

\*---------------------------------------------------------------------------*/


	#include "fvCFD.H"
	#include "simpleControl.H"
	#include "List.H"
	#include "Vessels.H"
	#include <iostream> 


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{

	#include "setRootCase.H"
	#include "createTime.H"
	#include "createMesh.H"
	#include "createFields.H"


	simpleControl simple(mesh);


	// DECLARATIONS


	// Creation of vessels (see Vessels.C and Vessels.H for additional information)

	Vessels artery1(0.001, 0.0015, 0.001, 0.001, 0.00001, 0.1);	
	Vessels vein1(0.001, 0.0005, 0.001, 0.001, 0.00001, 0.0);


	// Creation of index points associated to each vessel

	int a1 = artery1.pointIndex(mesh);
	int v1 = vein1.pointIndex(mesh);

	// CALCULATIONS


	while (simple.loop())
	{
		Info<< "Time = " << runTime.timeName() << nl << endl;

	
		// Write pressure and flow values

		Info << "Pressure at artery1 index " << P[a1] << nl
			<< "Artery1 flow rate " << q[a1] << nl
			<< "Pressure at vein1 index " << P[v1] << nl
			<< "Vein2 flow rate " << q[v1] << nl
			<< endl;
   

		while (simple.correctNonOrthogonal())
		{

			// Calculation of flow values

			q[a1] = artery1.flowRate(mesh, transportProperties, P);
			q[v1] = vein1.flowRate(mesh, transportProperties, P);


			// Resolution of the generalised Darcy equation

			fvScalarMatrix pEqn
			(
				fvm::ddt(epsc,P)
				- fvm::laplacian(K/mu, P) + q
		    	);
			pEqn.solve();


			// Application of the corrective well-model

			artery1.wellModel(mesh, transportProperties, P);
			vein1.wellModel(mesh, transportProperties, P);
			
		}


		// Calculation of the blood velocity

		U = -K/mu*fvc::grad(P);
		U.correctBoundaryConditions();

		#include "write.H"

		Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
			<< "  ClockTime = " << runTime.elapsedClockTime() << " s"
			<< nl << endl;
	}
    
    
	Info << "End\n" << endl;

	return 0;
}


// ************************************************************************* //
