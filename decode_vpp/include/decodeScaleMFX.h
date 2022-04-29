#ifndef DECODESCALEMFX_H
#define DECODESCALEMFX_H

#include "common_utils.h"
#include "cmd_options.h"

struct sInputParams
{
    mfxU32 videoType;
    bool bUseHWLib;
    bool bEnableOutput = false;
    mfxU16  Width;
    mfxU16  Height;
    mfxU32  fourcc;
    mfxU16  chromaType;
    char     strSrcFile[MSDK_MAX_PATH];
    char     strDstFile[MSDK_MAX_PATH];
};


class mfxDecodeVpp{
    public:
        mfxDecodeVpp();
        ~mfxDecodeVpp();
        
        mfxStatus Init(sInputParams *pParams);
        mfxStatus RunDecoding();
        void Destroy();
        
    
    protected:
        mfxStatus GetImpl(const sInputParams & params, mfxIMPL & impl);


    protected:
        mfxBitstream            m_mfxBS; // contains encoded data
        MFXVideoSession         m_mfxSession;
        mfxIMPL                 m_impl;
        MFXVideoDECODE*         m_pmfxDEC;
        MFXVideoVPP*            m_pmfxVPP;
        mfxVideoParam           m_videoParams;
        mfxU16                  m_vppOutWidth;
        mfxU16                  m_vppOutHeight;
        mfxStatus               m_error;
        mfxU32                  m_fourcc;
        bool                    m_bVppIsUsed;
        mfxVersion              m_ver;
        fileUniPtr              fSource;
        fileUniPtr              fSink;
        std::vector<mfxFrameSurface1> pmfxSurfaces;
        std::vector<mfxFrameSurface1> pmfxSurfaces2;
        bool bEnableOutput = false;
        char     strSrcFile[MSDK_MAX_PATH] = "/home/berkay/Downloads/test.h264";
        char     strDstFile[MSDK_MAX_PATH];

};




#endif


