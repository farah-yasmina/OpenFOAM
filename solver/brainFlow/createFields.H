	Info<< "Reading flow rate field\n" << endl;

	volScalarField q 
	(
		IOobject 
		(
			"q", 
			runTime.timeName(), 
			mesh, 
			IOobject::NO_READ, 
			IOobject::AUTO_WRITE 
		), 
		mesh,
		dimensionedScalar("q", dimensionSet(0,0,-1,0,0,0,0), 0.0)
	); 


    Info<< "Reading pressure field\n" << endl;
    
	volScalarField P
	(
		IOobject
		(
			"P",
			runTime.timeName(),
			mesh,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh
	);


	Info<< "Reading velocity field\n" << endl;

	volVectorField U
	(
		IOobject
		(
			"U",
			runTime.timeName(),
			mesh,
			IOobject::NO_READ,
			IOobject::AUTO_WRITE
		),
		mesh,
		dimensionedVector("U",dimensionSet(0,1,-1,0,0,0,0),vector::zero)
	);


	Info<< "Reading transportProperties\n" << endl;

	IOdictionary transportProperties
	(
		IOobject
		(
			"transportProperties",
			runTime.constant(),
			mesh,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	);


	Info<< "Reading porosity epsc\n" << endl;

	dimensionedScalar epsc
	(
		transportProperties.lookup("epsc")
	);

   
	Info<< "Reading permeability K\n" << endl;

	dimensionedScalar K
	(
		transportProperties.lookup("K")
	);
    

	Info<< "Reading dynamic viscosity mu\n" << endl;

	dimensionedScalar mu
	(
		transportProperties.lookup("mu")
	);    


#   include "createPhi.H"
