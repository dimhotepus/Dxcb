DirectX Command Buffer Lib
Version 1.0, 7/21/2008

See license.txt for copyright and license information.
________________________________________________________________________________
TABLE OF CONTENTS

    1. INTRODUCTION
    2. CONTENTS OF PACKAGE
    3. LIBRARY OVERVIEW
    4. SAMPLES
    5. VERSION HISTORY

________________________________________________________________________________
1. INTRODUCTION

The DirectX Command Buffer Library provides in-memory serialization of most 
calls to a Direct3D9 device, enabling recording and playback. This functionality 
allows parallel rendering from multiple threads. This package also contains 
small test applications for this library.

A presentation at Microsoft Gamefest 2008 discusses this library, and reviews 
measured performance improvements. That presentation can be found here: 
http://emergent.net/GameFest2008 

________________________________________________________________________________
2. CONTENTS OF PACKAGE

\AllDirectXCommandBuffer_2005.sln - Microsoft Visual Studio 2005 solution
                                    containing library and sample projects

\license.txt                      - License information

\readme.txt                       - This file

\DirectXCommandBufferLib          - Code for Library

\DXSamples                        - Samples

    \Instancing                   - Uses D3DEffects
    
    \Textures                     - Simple parallel rendering of DX Textures 
                                    sample
                                    
    \TexturesMultiThreaded        - Stress test sample included ability to
                                    dynamically scale thread count, per draw
                                    overhead, and draw call count

________________________________________________________________________________
3. LIBRARY OVERVIEW

Build process:

    The library makes use of macros to provide implementations for recording and 
    playing back command buffers. Permutations of the macros are required for 
    varying argument count. To ease the development of macros with consistent 
    functionality, spreadsheets are used to generate the various permutations.
    
    Debugging through code provided by macros is difficult, and so files using 
    macros are first preprocessed and then run through a code beautifier. This 
    is done by using custom build steps on selected files in the project.
    
    The code beautifier is GC.exe, or "Great Code", from the sourceforge project: 
    http://sourceforge.net/projects/gcgreatcode/

Key classes:

    CBMemoryBuffer
        
        A storage location for command buffers. These memory buffers are 
        allocated and managed by an application.

    CBRecorder9 
    
        Derived from the IDirect3DDevice9 interface, this class acts as a 
        "recording device". An application must first set the memory buffer with 
        SetCommandBuffer(), then call BeginCommandBuffer(). Rendering operations 
        can then be performed. Finally, EndCommandBuffer() should be called.
        
    CBPlayer9
    
        This class can be used to play back a command buffer on a real device.
        
    RedirectingDirect3DDevice9
    
        Derived from the IDirect3DDevice9 interface, this class acts as a device 
        and will pass through any calls to either a real device or another class 
        implementing the IDirect3DDevice9 interface.
        
        A pointer of a redirecting device can be given to classes, such as a 
        D3DEffect, that retain a pointer to a device. Then, the operation of 
        that device can be changed. E.g. when Effects are created they can be 
        given a true device, and then during rendering be redirected to a 
        command buffer.
        
    RedirectingEffectStateManager
    
        Similar to RedirectingDirect3DDevice9, and also located in the 
        RedirectingDirect3DDevice9.h file. This class wraps an 
        ID3DXEffectStateManager interface.
        
________________________________________________________________________________
4. SAMPLES

    Instancing
        
        Based off the DX sample, "Instancing", this sample uses command buffers 
        when in the "HWSkinning" mode. This sample's code is largely 
        experimental, contains many #ifdef statements trying different 
        approaches.
        
        This sample does use the D3DEffect classes with command buffers
        
    Textures
    
        Based off the DX tutorial sample, "Textures", this sample is a minimal 
        amount of code needed to perform rendering to command buffers from 
        multiple threads in parallel. 
        
        This sample is a good place to see what code is necessary to use this 
        library.
        
    TexturesMultiThreaded
        
        This is the best sample to use interactively to see the results
        of parallel command buffer recording.
    
        This sample greatly extends the "Texture" sample to add several 
        dynamically controllable parameters, and to facilitate measuring 
        performance results.

        The sample starts off with multithreading disabled. Press the "Toggle 
        MultiThreading" button to enable a slider that sets the recorder thread 
        count (these are in addition to the playback thread).
        
        The automated tested functionality appends to a log file 
        c:\testresults.txt
        
        "No Playback Overlap" forces all recording threads to complete, then 
        plays back all command buffers, then starts the next frame. Default 
        behavior is to play back command buffers from a previous frame while 
        recording the next.
        
________________________________________________________________________________ 
5. VERSION HISTORY

1.0 - Initial release

    - First version of library. Developed for and used in Gamefest presentation.
