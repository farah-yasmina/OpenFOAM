OpenFOAM
========

Files coded during the internship at Institut de Mécanique des Fluides de Toulouse

This project aims at calculating blood flow in the cerebral circulation. Since blood vessels in the brain are of varying diameters, two different models, based on two different characteristic dimensions, underpin this new model. On the one hand, big vessels like arteries, veins, arterioles and venules are represented as a porous network where the flow of blood answers to the Hagen-Poiseuille equation, which relates the flow rate to the differential pressure in a cylindrical pipe. On the other hand, the capillary bed is represented as a continuum, and is considered homogeneous on the Darcy scale. Blood flow in the capillary bed thus follows Darcy's law, which relates the instantaneous discharge rate to the differential pressure over a given distance.

The porous network model provides us with a throughput that is directly injected into the homogeneous medium at the junctions with the bigger vessels. However, the pressure computed following this injection varies with the mesh size and is not representative of the real pressure that is imposed on the tip of the vessel. Accounting for this approximation error required to develop a specific “well-model” (word used here by analogy with a nearly similar mathematical problem found in reservoir engineering).

Cf. the joined pdf file for further information and illustrations.


About OpenFOAM :
===============

"The OpenFOAM®  (Open Field Operation and Manipulation) CFD Toolbox is a free, open source CFD software package produced by OpenCFD Ltd. It has a large user base across most areas of engineering and science, from both commercial and academic organisations. OpenFOAM has an extensive range of features to solve anything from complex fluid flows involving chemical reactions, turbulence and heat transfer, to solid dynamics and electromagnetics. It includes tools for meshing, notably snappyHexMesh, a parallelised mesher for complex CAD geometries, and for pre- and post-processing. Almost everything (including meshing, and pre- and post-processing) runs in parallel as standard, enabling users to take full advantage of computer hardware at their disposal." -- http://www.openfoam.com/


Directory structure :
===================

- solver : the solver directory contains the main executable programs ("brainFlow" here).
- run : contains the desired cases on which to run the application ("test" here).


brainFlow/brainFlow.C :
----------------------

- Calculates blood pressure and flow in a cerebral vascular network.
- An applied example with one artery and one vein in a capillary network.
          
          
brainFlow/createFields.H :
------------------------
          
- The code for creating fields and reading field input data.
          
          
brainFlow/Vessels.C & Vessels.H :
-------------------------------
          
- Class of object "Vessel". Calculates blood flow & pressure distribution by applying a well model for arteries and veins.
          

run/test/0 :
----------
         
- Contains initial values of pressure distribution in the computational domain.


run/test/constant :
-----------------
         
- Subdirectory "polyMesh" : full description of the case mesh. The geometry is a cube with a rectilinear grid. It represents the capillary bed that is considered as a porous medium.
- File "transportProperties" : specifies physical properties for the application "brainFlow".


run/test/system :
---------------
         
- For setting parameters associated with the solution procedure itself.
