#include "decodeScaleMFX.h"
#include "iostream"



mfxDecodeVpp::mfxDecodeVpp() 
{
    m_mfxBS.MaxLength = 1024 * 1024;
    m_pmfxDEC = NULL;
    m_pmfxVPP = NULL;
    m_impl= 0;
    m_error = MFX_ERR_NONE;
    m_vppOutWidth  = 0;
    m_vppOutHeight = 0;
    m_fourcc = 0;
    m_bVppIsUsed = false;
    m_ver = {{0 , 1}};
    
    

}

mfxDecodeVpp::~mfxDecodeVpp()
{
    std::cout << "Closed. " << std::endl;
}


mfxStatus mfxDecodeVpp::Init(sInputParams *pParams)
{
    MSDK_CHECK_POINTER(pParams, MFX_ERR_NULL_PTR);
    m_error = MFX_ERR_NONE;

    fSource(OpenFile(pParams->strSrcFile,"rb"),CloseFile);
    MSDK_CHECK_POINTER(fSource,MFX_ERR_NULL_PTR);

    fSink(nullptr, CloseFile);
    if (pParams->bEnableOutput)
    {
        fSink.reset(OpenFile(pParams->strDstFile,"wb"));
        MSDK_CHECK_POINTER(fSink, MFX_ERR_NULL_PTR);
    }
    
    if(!pParams->bUseHWLib)
    {
        m_impl = MFX_IMPL_SOFTWARE;
    }

    m_impl = MFX_IMPL_HARDWARE_ANY;


    m_error = Initialize(m_impl,m_ver, &m_mfxSession, NULL);

    MSDK_CHECK_RESULT(m_error,MFX_ERR_NONE,m_error);

    m_pmfxDEC =new MFXVideoDECODE(m_mfxSession);
    m_pmfxVPP =new MFXVideoVPP (m_mfxSession);

    // MFXVideoDECODE mfxDEC(session);
    // // Create Media SDK VPP component
    // MFXVideoVPP mfxVPP(session);
    
    m_videoParams.mfx.CodecId = MFX_CODEC_AVC;
    m_videoParams.IOPattern = MFX_IOPATTERN_OUT_VIDEO_MEMORY;

    m_mfxBS.MaxLength = 1024 * 1024;
    std::vector<mfxU8> bstData(m_mfxBS.MaxLength);
    

    // m_error = ReadBitStreamData(&m_mfxBS, fSource.get());
    // MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    m_error = m_pmfxDEC->DecodeHeader(&m_mfxBS,&m_videoParams);
    MSDK_IGNORE_MFX_STS(m_error, MFX_WRN_PARTIAL_ACCELERATION);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);


    //Initialize VPP Params
    mfxVideoParam VPPParams;
    memset(&VPPParams, 0, sizeof(VPPParams));
    // Input data
    VPPParams.vpp.In.FourCC = MFX_FOURCC_NV12;
    VPPParams.vpp.In.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
    VPPParams.vpp.In.CropX = 0;
    VPPParams.vpp.In.CropY = 0;
    VPPParams.vpp.In.CropW = m_videoParams.mfx.FrameInfo.CropW;
    VPPParams.vpp.In.CropH = m_videoParams.mfx.FrameInfo.CropH;
    VPPParams.vpp.In.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
    VPPParams.vpp.In.FrameRateExtN = 30;
    VPPParams.vpp.In.FrameRateExtD = 1;
    // width must be a multiple of 16
    // height must be a multiple of 16 in case of frame picture and a multiple of 32 in case of field picture
    VPPParams.vpp.In.Width = MSDK_ALIGN16(VPPParams.vpp.In.CropW);
    VPPParams.vpp.In.Height =
        (MFX_PICSTRUCT_PROGRESSIVE == VPPParams.vpp.In.PicStruct) ?
        MSDK_ALIGN16(VPPParams.vpp.In.CropH) :
        MSDK_ALIGN32(VPPParams.vpp.In.CropH);
    // Output data
    VPPParams.vpp.Out.FourCC = MFX_FOURCC_NV12;
    VPPParams.vpp.Out.ChromaFormat = MFX_CHROMAFORMAT_YUV420;
    VPPParams.vpp.Out.CropX = 0;
    VPPParams.vpp.Out.CropY = 0;
    VPPParams.vpp.Out.CropW = VPPParams.vpp.In.CropW / 2;   // Resize to half size resolution
    VPPParams.vpp.Out.CropH = VPPParams.vpp.In.CropH / 2;
    VPPParams.vpp.Out.PicStruct = MFX_PICSTRUCT_PROGRESSIVE;
    VPPParams.vpp.Out.FrameRateExtN = 30;
    VPPParams.vpp.Out.FrameRateExtD = 1;
    // width must be a multiple of 16
    // height must be a multiple of 16 in case of frame picture and a multiple of 32 in case of field picture
    VPPParams.vpp.Out.Width = MSDK_ALIGN16(VPPParams.vpp.Out.CropW);
    VPPParams.vpp.Out.Height =
        (MFX_PICSTRUCT_PROGRESSIVE == VPPParams.vpp.Out.PicStruct) ?
        MSDK_ALIGN16(VPPParams.vpp.Out.CropH) :
        MSDK_ALIGN32(VPPParams.vpp.Out.CropH);

    VPPParams.IOPattern = MFX_IOPATTERN_IN_SYSTEM_MEMORY | MFX_IOPATTERN_OUT_SYSTEM_MEMORY;

    mfxFrameAllocRequest DecRequest; 
    m_error = m_pmfxDEC->QueryIOSurf(&m_videoParams, &DecRequest);
    MSDK_IGNORE_MFX_STS(m_error, MFX_WRN_PARTIAL_ACCELERATION);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    mfxFrameAllocRequest VPPRequest[2];     // [0] - in, [1] - out
    memset(&VPPRequest, 0, sizeof(mfxFrameAllocRequest) * 2);
    m_error = m_pmfxVPP->QueryIOSurf(&VPPParams, VPPRequest);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    mfxU16 nSurfNumDecVPP = DecRequest.NumFrameSuggested + VPPRequest[0].NumFrameSuggested;
    mfxU16 nSurfNumVPPOut = VPPRequest[1].NumFrameSuggested;
    


    // Allocate surfaces for decoder and VPP In
    // - Width and height of buffer must be aligned, a multiple of 32
    // - Frame surface array keeps pointers all surface planes and general frame info
    mfxU16 width = (mfxU16) MSDK_ALIGN32(DecRequest.Info.Width);
    mfxU16 height = (mfxU16) MSDK_ALIGN32(DecRequest.Info.Height);
    mfxU8 bitsPerPixel = 12;        // NV12 format is a 12 bits per pixel format
    mfxU32 surfaceSize = width * height * bitsPerPixel / 8;
    std::vector<mfxU8> surfaceBuffersData(surfaceSize * nSurfNumDecVPP);
    mfxU8* surfaceBuffers = surfaceBuffersData.data();

    std::vector<mfxFrameSurface1> pmfxSurfaces(nSurfNumDecVPP);
    for (int i = 0; i < nSurfNumDecVPP; i++) {
        memset(&pmfxSurfaces[i], 0, sizeof(mfxFrameSurface1));
        pmfxSurfaces[i].Info = m_videoParams.mfx.FrameInfo;
        pmfxSurfaces[i].Data.Y = &surfaceBuffers[surfaceSize * i];
        pmfxSurfaces[i].Data.U = pmfxSurfaces[i].Data.Y + width * height;
        pmfxSurfaces[i].Data.V = pmfxSurfaces[i].Data.U + 1;
        pmfxSurfaces[i].Data.Pitch = width;
    }


    // Allocate surfaces for VPP Out
    // - Width and height of buffer must be aligned, a multiple of 32
    // - Frame surface array keeps pointers all surface planes and general frame info
    width = (mfxU16) MSDK_ALIGN32(VPPRequest[1].Info.Width);
    height = (mfxU16) MSDK_ALIGN32(VPPRequest[1].Info.Height);
    bitsPerPixel = 12;      // NV12 format is a 12 bits per pixel format
    surfaceSize = width * height * bitsPerPixel / 8;
    std::vector<mfxU8> surfaceBuffersData2(surfaceSize * nSurfNumVPPOut);
    mfxU8* surfaceBuffers2 = surfaceBuffersData2.data();

    std::vector<mfxFrameSurface1> pmfxSurfaces2(nSurfNumVPPOut);
    for (int i = 0; i < nSurfNumVPPOut; i++) {
        memset(&pmfxSurfaces2[i], 0, sizeof(mfxFrameSurface1));
        pmfxSurfaces2[i].Info = VPPParams.vpp.Out;
        pmfxSurfaces2[i].Data.Y = &surfaceBuffers2[surfaceSize * i];
        pmfxSurfaces2[i].Data.U = pmfxSurfaces2[i].Data.Y + width * height;
        pmfxSurfaces2[i].Data.V = pmfxSurfaces2[i].Data.U + 1;
        pmfxSurfaces2[i].Data.Pitch = width;
    }

    m_error = m_pmfxDEC->Init(&m_videoParams);
    MSDK_IGNORE_MFX_STS(m_error, MFX_WRN_PARTIAL_ACCELERATION);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    // Initialize Media SDK VPP
    m_error = m_pmfxVPP->Init(&VPPParams);
    MSDK_IGNORE_MFX_STS(m_error, MFX_WRN_PARTIAL_ACCELERATION);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    std::cout << width << std::endl; 

}


mfxStatus mfxDecodeVpp::RunDecoding()
{
    mfxTime tStart, tEnd;
    mfxGetTime(&tStart);
    // fileUniPtr fSource(OpenFile(strSrcFile,"rb"),&CloseFile);
    // fileUniPtr fSink(OpenFile(strDstFile,"wb"),&CloseFile);
    

    mfxSyncPoint syncpD;
    mfxSyncPoint syncpV;
    mfxFrameSurface1* pmfxOutSurface = NULL;
    int nIndex = 0;
    int nIndex2 = 0;
    mfxU32 nFrame = 0;
    while (MFX_ERR_NONE <= m_error || MFX_ERR_MORE_DATA == m_error || MFX_ERR_MORE_SURFACE == m_error) {
        if (MFX_WRN_DEVICE_BUSY == m_error)
            MSDK_SLEEP(1);  // Wait if device is busy, then repeat the same call to DecodeFrameAsync

        if (MFX_ERR_MORE_DATA == m_error) {
            m_error = ReadBitStreamData(&m_mfxBS, fSource.get());       // Read more data into input bit stream
            MSDK_BREAK_ON_ERROR(m_error);
        }

        if (MFX_ERR_MORE_SURFACE == m_error || MFX_ERR_NONE == m_error) {
            nIndex = GetFreeSurfaceIndex(pmfxSurfaces);     // Find free frame surface
            MSDK_CHECK_ERROR(MFX_ERR_NOT_FOUND, nIndex, MFX_ERR_MEMORY_ALLOC);
        }
        // Decode a frame asychronously (returns immediately)
        m_error = m_pmfxDEC->DecodeFrameAsync(&m_mfxBS, &pmfxSurfaces[nIndex], &pmfxOutSurface, &syncpD);

        // Ignore warnings if output is available,
        // if no output and no action required just repeat the DecodeFrameAsync call
        if (MFX_ERR_NONE < m_error && syncpD)
            m_error = MFX_ERR_NONE;

        if (MFX_ERR_NONE == m_error) {
            nIndex2 = GetFreeSurfaceIndex(pmfxSurfaces2);   // Find free frame surface
            MSDK_CHECK_ERROR(MFX_ERR_NOT_FOUND, nIndex2, MFX_ERR_MEMORY_ALLOC);

            for (;;) {
                // Process a frame asychronously (returns immediately)
                m_error = m_pmfxVPP->RunFrameVPPAsync(pmfxOutSurface, &pmfxSurfaces2[nIndex2], NULL, &syncpV);

                if (MFX_ERR_NONE < m_error && !syncpV) {    // repeat the call if warning and no output
                    if (MFX_WRN_DEVICE_BUSY == m_error)
                        MSDK_SLEEP(1);  // wait if device is busy
                } else if (MFX_ERR_NONE < m_error && syncpV) {
                    m_error = MFX_ERR_NONE;     // ignore warnings if output is available
                    break;
                } else
                    break;  // not a warning
            }

            // VPP needs more data, let decoder decode another frame as input
            if (MFX_ERR_MORE_DATA == m_error) {
                continue;
            } else if (MFX_ERR_MORE_SURFACE == m_error) {
                // Not relevant for the illustrated workload! Therefore not handled.
                // Relevant for cases when VPP produces more frames at output than consumes at input. E.g. framerate conversion 30 fps -> 60 fps
                break;
            } else
                MSDK_BREAK_ON_ERROR(m_error);
        }

        if (MFX_ERR_NONE == m_error)
            m_error = m_mfxSession.SyncOperation(syncpV, 60000);     // Synchronize. Wait until decoded frame is ready

        if (MFX_ERR_NONE == m_error) {
            ++nFrame;
            if (bEnableOutput) {
                m_error = WriteRawFrame(&pmfxSurfaces2[nIndex2], fSink.get());
                MSDK_BREAK_ON_ERROR(m_error);

                printf("Frame number: %d\r", nFrame);
            }
        }
    }

    // MFX_ERR_MORE_DATA means that file has ended, need to go to buffering loop, exit in case of other errors
    MSDK_IGNORE_MFX_STS(m_error, MFX_ERR_MORE_DATA);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    //
    // Stage 2: Retrieve the buffered decoded frames
    //
    while (MFX_ERR_NONE <= m_error || MFX_ERR_MORE_SURFACE == m_error) {
        if (MFX_WRN_DEVICE_BUSY == m_error)
            MSDK_SLEEP(1);  // Wait if device is busy, then repeat the same call to DecodeFrameAsync

        nIndex = GetFreeSurfaceIndex(pmfxSurfaces);     // Find free frame surface
        MSDK_CHECK_ERROR(MFX_ERR_NOT_FOUND, nIndex, MFX_ERR_MEMORY_ALLOC);

        // Decode a frame asychronously (returns immediately)
        m_error = m_pmfxDEC->DecodeFrameAsync(NULL, &pmfxSurfaces[nIndex], &pmfxOutSurface, &syncpD);

        // Ignore warnings if output is available,
        // if no output and no action required just repeat the DecodeFrameAsync call
        if (MFX_ERR_NONE < m_error && syncpD)
            m_error = MFX_ERR_NONE;

        if (MFX_ERR_NONE == m_error) {
            nIndex2 = GetFreeSurfaceIndex(pmfxSurfaces2);   // Find free frame surface
            MSDK_CHECK_ERROR(MFX_ERR_NOT_FOUND, nIndex2, MFX_ERR_MEMORY_ALLOC);

            for (;;) {
                // Process a frame asychronously (returns immediately)
                m_error = m_pmfxVPP->RunFrameVPPAsync(pmfxOutSurface, &pmfxSurfaces2[nIndex2], NULL, &syncpV);

                if (MFX_ERR_NONE < m_error && !syncpV) {    // repeat the call if warning and no output
                    if (MFX_WRN_DEVICE_BUSY == m_error)
                        MSDK_SLEEP(1);  // wait if device is busy
                } else if (MFX_ERR_NONE < m_error && syncpV) {
                    m_error = MFX_ERR_NONE;     // ignore warnings if output is available
                    break;
                } else
                    break;  // not a warning
            }

            // VPP needs more data, let decoder decode another frame as input
            if (MFX_ERR_MORE_DATA == m_error) {
                continue;
            } else if (MFX_ERR_MORE_SURFACE == m_error) {
                // Not relevant for the illustrated workload! Therefore not handled.
                // Relevant for cases when VPP produces more frames at output than consumes at input. E.g. framerate conversion 30 fps -> 60 fps
                break;
            } else
                MSDK_BREAK_ON_ERROR(m_error);
        }

        if (MFX_ERR_NONE == m_error)
            m_error = m_mfxSession.SyncOperation(syncpV, 60000);     // Synchronize. Waits until decoded frame is ready

        if (MFX_ERR_NONE == m_error) {
            ++nFrame;
            if (bEnableOutput) {
                m_error = WriteRawFrame(&pmfxSurfaces2[nIndex2], fSink.get());
                MSDK_BREAK_ON_ERROR(m_error);

                printf("Frame number: %d\r", nFrame);
            }
        }
    }

    // MFX_ERR_MORE_DATA means that decoder is done with buffered frames, need to go to VPP buffering loop, exit in case of other errors
    MSDK_IGNORE_MFX_STS(m_error, MFX_ERR_MORE_DATA);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    //
    // Stage 3: Retrieve the buffered VPP frames
    //
    while (MFX_ERR_NONE <= m_error) {
        nIndex2 = GetFreeSurfaceIndex(pmfxSurfaces2);   // Find free frame surface
        MSDK_CHECK_ERROR(MFX_ERR_NOT_FOUND, nIndex2, MFX_ERR_MEMORY_ALLOC);

        // Process a frame asychronously (returns immediately)
        m_error = m_pmfxVPP->RunFrameVPPAsync(NULL, &pmfxSurfaces2[nIndex2], NULL, &syncpV);
        MSDK_IGNORE_MFX_STS(m_error, MFX_ERR_MORE_SURFACE);
        MSDK_BREAK_ON_ERROR(m_error);

        m_error = m_mfxSession.SyncOperation(syncpV, 60000);     // Synchronize. Wait until frame processing is ready
        MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

        ++nFrame;
        if (bEnableOutput) {
            m_error = WriteRawFrame(&pmfxSurfaces2[nIndex2], fSink.get());
            MSDK_BREAK_ON_ERROR(m_error);

            printf("Frame number: %d\r", nFrame);
        }
    }

    // MFX_ERR_MORE_DATA indicates that all buffers has been fetched, exit in case of other errors
    MSDK_IGNORE_MFX_STS(m_error, MFX_ERR_MORE_DATA);
    MSDK_CHECK_RESULT(m_error, MFX_ERR_NONE, m_error);

    mfxGetTime(&tEnd);
    double elapsed = TimeDiffMsec(tEnd, tStart) / 1000;
    double fps = ((double)nFrame / elapsed);
    printf("\nExecution time: %3.2f s (%3.2f fps)\n", elapsed, fps);

    Destroy();
    Release();
}


void mfxDecodeVpp::Destroy()
{
    m_pmfxDEC->Close();
    m_pmfxVPP->Close();
}