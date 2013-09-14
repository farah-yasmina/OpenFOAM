    if (runTime.outputTime())
    {
        volVectorField gradP(fvc::grad(P));

        volScalarField gradPx
        (
            IOobject
            (
                "gradPx",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradP.component(vector::X)
        );

        volScalarField gradPy
        (
            IOobject
            (
                "gradPy",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradP.component(vector::Y)
        );

        volScalarField gradPz
        (
            IOobject
            (
                "gradPz",
                runTime.timeName(),
                mesh,
                IOobject::NO_READ,
                IOobject::AUTO_WRITE
            ),
            gradP.component(vector::Z)
        );


        runTime.write();
    }
