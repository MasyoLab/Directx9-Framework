xof 0303txt 0032

Frame Root {
  FrameTransformMatrix {
     1.000000, 0.000000, 0.000000, 0.000000,
     0.000000,-0.000000, 1.000000, 0.000000,
     0.000000, 1.000000, 0.000000, 0.000000,
     0.000000, 0.000000, 0.000000, 1.000000;;
  }
  Frame Box {
    FrameTransformMatrix {
       1.000000, 0.000000, 0.000000, 0.000000,
       0.000000, 1.000000, 0.000000, 0.000000,
       0.000000, 0.000000, 1.000000, 0.000000,
       0.000000, 0.000000, 0.000000, 1.000000;;
    }
    Mesh { // Box mesh
      8;
      -0.500000;-0.500000;-0.500000;,
      -0.500000;-0.500000; 0.500000;,
      -0.500000; 0.500000;-0.500000;,
      -0.500000; 0.500000; 0.500000;,
       0.500000;-0.500000;-0.500000;,
       0.500000;-0.500000; 0.500000;,
       0.500000; 0.500000;-0.500000;,
       0.500000; 0.500000; 0.500000;;
      6;
      4;2,3,1,0;,
      4;6,7,3,2;,
      4;4,5,7,6;,
      4;0,1,5,4;,
      4;0,4,6,2;,
      4;5,1,3,7;;
      MeshNormals { // Box normals
        6;
        -1.000000;-0.000000; 0.000000;,
         0.000000; 1.000000; 0.000000;,
         1.000000;-0.000000; 0.000000;,
         0.000000;-1.000000; 0.000000;,
         0.000000; 0.000000;-1.000000;,
         0.000000;-0.000000; 1.000000;;
        6;
        4;0,0,0,0;,
        4;1,1,1,1;,
        4;2,2,2,2;,
        4;3,3,3,3;,
        4;4,4,4,4;,
        4;5,5,5,5;;
      } // End of Box normals
    } // End of Box mesh
  } // End of Box
} // End of Root