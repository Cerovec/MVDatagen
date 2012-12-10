% Da bi se mex mogao uspjesno linkati na projekte u Photopayu u onim projektima o kojima ovisim
% potrebno je dodati -fPIC yastavicu u CXXFLAGS
% 
% 
% Nakon sto je uspio kompajlirat morao sam mu dat noviji lib od onog koji dolazi s matlabom
% sudo ln -s /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.17 matlabroot/sys/os/glnxa64/libstdc++.so.6
% 
% Za razlicite operacijske sustave treba posebno kompajlirati


mex -outdir ./ -output MVDatagenMatlab -largeArrayDims -cxx -DMATLAB -DUSE_GLX -DGL_GLEXT_PROTOTYPES -I../Source -I../../CoreUtils/Source -I../../GPUMVToolset/Source/ -L../Build -lMVDatagen -L../../GPUMVToolset/Build -lGPUMVToolset -L../../CoreUtils/Build -lCoreUtils -lopencv_core -lopencv_highgui -lopencv_imgproc -lGL -lX11 matlabLink.cpp