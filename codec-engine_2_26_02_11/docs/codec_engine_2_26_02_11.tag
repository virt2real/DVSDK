<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>Codec Engine API Reference</title>
    <filename>index</filename>
    <docanchor file="index">modules</docanchor>
  </compound>
  <compound kind="file">
    <name>auddec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio/</path>
    <filename>auddec_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iauddec_8h" name="iauddec.h" local="no" imported="no">ti/xdais/dm/iauddec.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_EOK</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5aadb97b6280f6e82207dae35a19ab75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_EFAIL</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gac525735408fd0a7afd12dd377bbf060d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_ERUNTIME</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gae83a152915d35026cdb65751ed07348a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_ETIMEOUT</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga27ab905518ac056065d4b88bce101885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_FOREVER</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga68744c319229a47b80856511a560ce56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_Status</type>
      <name>AUDDEC_Status</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0d82470b3aa6bc16eb5ac0667e43a611</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDDEC_Handle</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9a4e2b0c3961b3ca9963bd53394f5376</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Params</type>
      <name>AUDDEC_Params</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gaf6b50d59060abcc0f793f30860cdc1fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_InArgs</type>
      <name>AUDDEC_InArgs</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gaa7db0270c5e9c3f5f96e20044e22e715</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_OutArgs</type>
      <name>AUDDEC_OutArgs</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gadd938b8170a9e1b1b599035bb5918917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_Cmd</type>
      <name>AUDDEC_Cmd</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga90e760cacdf6a9ea4c15a9a8952a5fb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_DynamicParams</type>
      <name>AUDDEC_DynamicParams</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga050b8f4d86a988ad5315a053cf2e623e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>AUDDEC_Handle</type>
      <name>AUDDEC_create</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gae6ed4b3e8a66743baf5a4ae65e382318</anchor>
      <arglist>(Engine_Handle e, String name, AUDDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC_process</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5f07d733ba7987df8a334263fc01113e</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC_control</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga2f774103e5122bf6cfa0cccb7b2bccdb</anchor>
      <arglist>(AUDDEC_Handle handle, AUDDEC_Cmd id, AUDDEC_DynamicParams *params, AUDDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDDEC_delete</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0ab1678bca5777911d621676f7ecf202</anchor>
      <arglist>(AUDDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDDEC_processAsync</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga429d9453059105c64cdd62258ee4bda1</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDDEC_processWait</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga07f8e317523dcaf9dfe58ebe56b53685</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>auddec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio1/</path>
    <filename>auddec1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iauddec1_8h" name="iauddec1.h" local="no" imported="no">ti/xdais/dm/iauddec1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga7cae0178b745ced9741f73c78b14cc59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga7b362018715454a7cd69d3852a45713c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga897c4f1874face10e1445ac6bf6e0610</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga367a626a0619b14d2bf621017ba5489d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9c3af29d4795a05bcf8312f79614cfbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga1f8a3080f30308909e6a16e935cddc77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Params</type>
      <name>AUDDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9f31560ab1264f8819e828a05b1ede43</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_InArgs</type>
      <name>AUDDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gacaf3e3bbdafd81372ae2a5ad2b62f043</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_OutArgs</type>
      <name>AUDDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaddc74dbbd57b740bd39747df2b7c8b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_Cmd</type>
      <name>AUDDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga3a5878eef18304b679d71bba5ccbdb2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_Status</type>
      <name>AUDDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga0d7173984244221930950e73fede03fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_DynamicParams</type>
      <name>AUDDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga459675fe5d579d089e3dabac96c2decc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gad6a763c59bef6cbbf42229fadd59996c</anchor>
      <arglist>(AUDDEC1_Handle handle, AUDDEC1_Cmd id, AUDDEC1_DynamicParams *params, AUDDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>AUDDEC1_Handle</type>
      <name>AUDDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaea018c45115cbd0a8770533652d64605</anchor>
      <arglist>(Engine_Handle e, String name, AUDDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga598c49e01a1bb081056878ff684c255d</anchor>
      <arglist>(AUDDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga6c56308ce43be75e9bfde187d3cf9857</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gac3be9dd65f18ca77540104e729c75492</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4e96ed949f9e2e895e9b7af97da64472</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>audenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio/</path>
    <filename>audenc_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iaudenc_8h" name="iaudenc.h" local="no" imported="no">ti/xdais/dm/iaudenc.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_EOK</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga4c5cbf3bf71fcbc6bbf29f1f32fdf852</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_EFAIL</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gad908fbd7c4b483bfa39be10b9c834ce9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_ERUNTIME</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf875d4b5e97d143e8d882801bf7c88dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_ETIMEOUT</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gacd92898b4599b439cfd3228b29220696</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_FOREVER</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga5ca7c02759b1a62dc67b8d30cdd9f0e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_Status</type>
      <name>AUDENC_Status</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga7d46b31739a556dd457b7ab32764788b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDENC_Handle</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga855d8e711a8401f488094e2ec7efcd51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Params</type>
      <name>AUDENC_Params</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga45a398c8eecb36cff04ebeecf3dbd258</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_InArgs</type>
      <name>AUDENC_InArgs</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga08bdf4d2128042a91f7b5abee25f5671</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_OutArgs</type>
      <name>AUDENC_OutArgs</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gab58c6abd4ac79581f24335f3392ccee3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_Cmd</type>
      <name>AUDENC_Cmd</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf6be17656a84026d539cbc9206c2640f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_DynamicParams</type>
      <name>AUDENC_DynamicParams</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga595199f736ff81270764c1e2073c119c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>AUDENC_Handle</type>
      <name>AUDENC_create</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga7bd1200782629a1654c47a49b0afbbcc</anchor>
      <arglist>(Engine_Handle e, String name, AUDENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC_process</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2a80fee7800e81fee57d2797a8759e2d</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDENC_InArgs *inArgs, AUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC_control</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaeff5234573e4c2aa429164c28772fdd0</anchor>
      <arglist>(AUDENC_Handle handle, AUDENC_Cmd id, AUDENC_DynamicParams *params, AUDENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDENC_delete</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaaca35ba0e092775f695cdfafd975a222</anchor>
      <arglist>(AUDENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDENC_processAsync</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaaeddbf9dd9c4d6690c2dbb2732d2d262</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDENC_processWait</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gac3d34c85e0d4859b8f45fa76445ce7e6</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>audenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio1/</path>
    <filename>audenc1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iaudenc1_8h" name="iaudenc1.h" local="no" imported="no">ti/xdais/dm/iaudenc1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad041cdb795eb67ed045070f3a5b8e02f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab7afa90b2e5f36f30e5bb40d47ed3a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad1884d423418d2ab65fc68e53b852d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab33f23be8d3ccc4359abe5e5b40339e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga69188768596074074cd78e022b82cc74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga8ea092f42c3ab3ae85939be5665cf6ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Params</type>
      <name>AUDENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga65c939059ccca8d6ae568d1f74d90d82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_InArgs</type>
      <name>AUDENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga2acdfe2b6adcdef65eeae4117b4b5c0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_OutArgs</type>
      <name>AUDENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga68ea1073c2c7a63a3ae592ee863a6d66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_Cmd</type>
      <name>AUDENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga11153a4a24f6302e33a4864182f3aadc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_Status</type>
      <name>AUDENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gafd9444abf1e55e5f485be698c6c2d32d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_DynamicParams</type>
      <name>AUDENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga067151e76cb3a8b3280c19d53e2b1b77</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_control</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab51d1cb8d0eaf13f828d8b1da4cc35b6</anchor>
      <arglist>(AUDENC1_Handle handle, AUDENC1_Cmd id, AUDENC1_DynamicParams *params, AUDENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>AUDENC1_Handle</type>
      <name>AUDENC1_create</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad20840f08b1d1c665ff274a94548bc4a</anchor>
      <arglist>(Engine_Handle e, String name, AUDENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga12b1afd6e52710a3b7c9e7f89fc552bf</anchor>
      <arglist>(AUDENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_process</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3bd9752523d729a6ccfe4bd9e554e55a</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaafc736b175b11fd5b7a05e5dbc8c37a1</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga499821481f85edc25d6e7295a2417231</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>CERuntime.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/</path>
    <filename>_c_e_runtime_8h</filename>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>CE_NULL_algs</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga687607b8a6f12ca612707cb6d11583b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_DECLARE_TYPE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gac50d12c52d8d4aac6d76992454c2dad0</anchor>
      <arglist>(name, types)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_LOCAL_ALG</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafa86c420c31be63be93489ca63c7d174</anchor>
      <arglist>(name, algName, ialgFxns, idma3Fxns, iresFxns, groupId, memType)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_BEGIN_ALG_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gacf6ab4ebae6dd399688b98e13d21ceaa</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_END_ALG_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga115a7b326a0a7fde5127ad8a523b9763</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_ENGINE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad994d600966e4ba100cc710d5ab32af5</anchor>
      <arglist>(algTab, engineName, serverName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_BEGIN_ENGINE_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab542c08643ed464fb2fb97882d72548a</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_END_ENGINE_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga6d8741a755739533403cb5b151c5b1b4</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>CERuntime_exit</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gae81e229a6d09ac5c102cf76bac61b5c9</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>CERuntime_init</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga624b5013c5e945115f1cb24d91e4bb1d</anchor>
      <arglist>(Void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>disclaimer.dox</name>
    <path>/db/toolsrc/library/tools/default/doxygen_templates/</path>
    <filename>disclaimer_8dox</filename>
  </compound>
  <compound kind="file">
    <name>doxygen.txt</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/</path>
    <filename>doxygen_8txt</filename>
  </compound>
  <compound kind="file">
    <name>Engine.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/</path>
    <filename>_engine_8h</filename>
    <includes id="_server_8h" name="Server.h" local="no" imported="no">ti/sdo/ce/Server.h</includes>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <class kind="struct">Engine_Attrs</class>
    <class kind="struct">Engine_AlgInfo</class>
    <class kind="struct">Engine_AlgInfo2</class>
    <member kind="define">
      <type>#define</type>
      <name>Engine_GTNAME</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga11643a7e887b00dd2650bb1ca2732a7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EOK</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaf8bb60516b74105725e58412a88db1e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EEXIST</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga0f8fa096a63966a75462564312a3bd66</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOMEM</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3ee58dda6fc9f978795f3cea8e2020c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EDSPLOAD</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga1e606dbc394478386aefe4bc5b3abfa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOCOMM</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafe977b3ced21706146f17a13bf14ef93</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOSERVER</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga22591f7ad9c65dbff089ef9e1fbd9e85</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECOMALLOC</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4525910605d2e130d56375a1fbf68670</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ERUNTIME</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga432f689c4e041b891e1f684be26fb6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECODECCREATE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaf1540d3614ae2319c6b58e61ea9da113</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECODECSTART</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3997d0a7c94029d986d65265c44d5ab7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EINVAL</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gadfe8054a16e0d418121dbc85627907f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EBADSERVER</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga2439ba2928ca9b6fcdc07747103e6d8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOTAVAIL</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga12a509dcf682511e67b2ea55d44057a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EWRONGSTATE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga79536865c47e6bc79a29b4b0579b3767</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EINUSE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga94a32c2e92fe465e882d3f3ab28c3ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOTFOUND</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaae6c26e072b54d7391d3e3e38156c0fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ETIMEOUT</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad11ff34d807f5333fd6da55c6e7c5d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct Engine_Obj *</type>
      <name>Engine_Handle</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga959793a179df69888545ae97ea5133f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int</type>
      <name>Engine_Error</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab52682a9391cdc982bed4d1182dd45a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Engine_close</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga59dcc500dd2d79d8b010966aaaa81168</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Handle</type>
      <name>Engine_open</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab8727c3396b518f7ceb9b6deadd3087b</anchor>
      <arglist>(String name, Engine_Attrs *attrs, Engine_Error *ec)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_fwriteTrace</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4ce94c8f9c8d5a2e18b5e0b18babc0fb</anchor>
      <arglist>(Engine_Handle engine, String prefix, FILE *out)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getAlgInfo</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga48e46d28d6255d83df21f1b71046b6f1</anchor>
      <arglist>(String name, Engine_AlgInfo *algInfo, Int index)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getAlgInfo2</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga7bf5ed04f4f5b3c986afce20aa2fb123</anchor>
      <arglist>(String name, Engine_Handle engine, Engine_AlgInfo2 *algInfo2, Int index)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_getCpuLoad</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga490ba2a1ced016d81b382173ef45e36a</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getLastError</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafbac0d441fe395cd5bd4766b11981653</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>Engine_getName</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4d3564bb008d9125ec552d38d882e4c4</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getNumAlgs</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3e2dca6a4e33ab6e39360eb80e4be2ea</anchor>
      <arglist>(String name, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getNumAlgs2</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga7e91e8e5b6afd0381682cab6fae7fa6f</anchor>
      <arglist>(String name, Engine_Handle engine, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Handle</type>
      <name>Engine_getServer</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad66457f2cf1c4689df5a861e82fdee0e</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>UInt32</type>
      <name>Engine_getUsedMem</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaaaa0c364a45c1da8df0c9e1bf4aa66b9</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_setTrace</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gabb16d952ee17a7744ec84cb7e837f458</anchor>
      <arglist>(Engine_Handle engine, String mask)</arglist>
    </member>
    <member kind="variable">
      <type>Engine_Attrs</type>
      <name>Engine_ATTRS</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga189a5d439a3afb93d283e8476d504d60</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ialg.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/</path>
    <filename>ialg_8h</filename>
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IALG_DEFMEMRECS</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga8a220fa863380937542f6a38be47ceda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_OBJMEMREC</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga0e3202a4d8dc0bd3cb300633922ffd54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_SYSCMD</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga200f155f9e2720011270e99f17bb6675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EOK</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga2c15898121a23a164e4ea2bcc4f7e7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EFAIL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga604e5600815cbd58846e0c5c05b6ba18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILBASE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga1f655af6b5ce37aaf5328243d1993cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILEND</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafbab7f3470d8b5a46615f1aca5c739b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga86018453b8f991c8cb545b2e43c80c9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MXTRN</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafc53b940e2982a2e859bda0555180eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isProg</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga93e8704d8e88d2f3dde1a85317232b59</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isOffChip</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gae2530ce6b07542f579871961a3fcfd4f</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj *</type>
      <name>IALG_Handle</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga16c037803ea218ba3dc5158f55ef27c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>IALG_Cmd</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9032f20923ef2ba1d6b88c87a20075fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SCRATCH</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da85e0509f7e82ebd01b57f899122de9b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_PERSIST</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da68adbe0194074e0474333b76f7d1e090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_WRITEONCE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da42356e6aa11869bfd15f31472f49a7c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6410b22d1d073ab55b289ca2f3c03b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_IPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a946577db145f691f81d7085fc51e2201</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_ESDATA</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a85fff905ed5e83445e3424ce5ba03175</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa98151c21c55ddaf8c1918d8007e5493</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497af6a85bf972a4d090e2c0e4d31565f879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497ad7b3b18fc0263be0f0702d263f600d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa5c6d8cfdb63c11fafd22bb87204c5cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4b31d959f6af27a012a87957c05d9c4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4ac938c5e58e4d4a30458b63869f0095</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a17fc19eac565b29871efbfed54760414</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6db79aaafcf9b4354f2828c2a94b8590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iauddec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iauddec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDDEC_Obj</class>
    <class kind="struct">IAUDDEC_Params</class>
    <class kind="struct">IAUDDEC_DynamicParams</class>
    <class kind="struct">IAUDDEC_InArgs</class>
    <class kind="struct">IAUDDEC_Status</class>
    <class kind="struct">IAUDDEC_OutArgs</class>
    <class kind="struct">IAUDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gae550832bf925622e32ea891f9a64f840</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0447e3d9eba91c950b0ca6533f090b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9ba0561ce6c276ef9a4b9d6dc1b66aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacfdf5e7ab31ee37a9b168bbcf7d71309</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj *</type>
      <name>IAUDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga849224ef7d8add16e7152e3c2cef1cb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga8a44a541760fefd4c41ea1d29c80d71e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iauddec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iauddec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDDEC1_Obj</class>
    <class kind="struct">IAUDDEC1_Params</class>
    <class kind="struct">IAUDDEC1_DynamicParams</class>
    <class kind="struct">IAUDDEC1_InArgs</class>
    <class kind="struct">IAUDDEC1_Status</class>
    <class kind="struct">IAUDDEC1_OutArgs</class>
    <class kind="struct">IAUDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2875d67b3c5af6d7a16b373ec21cf567</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2ac49534acb4a9fef6c32355b9883664</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga690d6e129037630a13d1b80eb1e2480d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj *</type>
      <name>IAUDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2287de2327bdc6e94ada6971506a2fe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4c0ee4ad90447b42d3a39dd6e81ca3c7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iaudenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDENC_Obj</class>
    <class kind="struct">IAUDENC_Params</class>
    <class kind="struct">IAUDENC_DynamicParams</class>
    <class kind="struct">IAUDENC_InArgs</class>
    <class kind="struct">IAUDENC_Status</class>
    <class kind="struct">IAUDENC_OutArgs</class>
    <class kind="struct">IAUDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2c2cde30bd98faf8f6e88058e766c432</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gac95ad430142a56f43f9f822372cd55fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga277eb1ae03f2becd10f2e62804e68876</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga8955b9b4eff0b4105d71a7e13e4b1292</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj *</type>
      <name>IAUDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga67b207a9e6d7ac649cf393bf9b89a758</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga875abe1167c5304cec0cb23421f3215a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iaudenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="iaudio_8h" name="iaudio.h" local="yes" imported="no">iaudio.h</includes>
    <class kind="struct">IAUDENC1_Obj</class>
    <class kind="struct">IAUDENC1_Params</class>
    <class kind="struct">IAUDENC1_DynamicParams</class>
    <class kind="struct">IAUDENC1_InArgs</class>
    <class kind="struct">IAUDENC1_Status</class>
    <class kind="struct">IAUDENC1_OutArgs</class>
    <class kind="struct">IAUDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaca757d01864682f891f4e79e27612615</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3b351ca3f8350018b9411570be9a0e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gace019d488c6e5825adcf3950246b2ea5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj *</type>
      <name>IAUDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga674429c3839d2412844c94f288c88493</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab08988284a4cb6779e196509c28705d0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iaudio.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iaudio_8h</filename>
    <member kind="enumeration">
      <name>IAUDIO_ChannelId</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga2f7957b5da562687498a612165664179</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_MONO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a5f4470f75c884f7e4b04ca5f14ad7acf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_STEREO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a99e682b79cf46c280e7bafb9470b8f2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_THREE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179aeabcf85e87c1c856a80b9824220aaaa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a9f5cb587cdcfb58952ecebce56532568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a05f535ae3ec20c8f007b9139eda2be73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_SEVEN_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a092297b5eee8fa4bf24b7bac35a5c8ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_ChannelMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga42c416b540264a57d8728b07d765b14d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_1_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da4a44a2c8361fe98d5a083c7a067933e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da8cf64356a7097cea1e401ab31d7f5f8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_11_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da97b04f3a5f55abc03ec813694b1236d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da66f93b5b1244b8c4386f7f2bfdd81783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da1f7b4e0d6455df92a428c33848351b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da77f0db8024cbb1df8d501f11b3b6ee11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dacafa604d4031971085a63e74c6a1377a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dac912907baaca2ef193290fb54359d022</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da022f51b4b16ed20be3a67fba6247a54a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dae2eaa060c3dc06e7126eb088f2639466</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_4</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da0de8b72246498dc39781fa6f8f88feb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_DualMonoMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga3d6a55ad8d567db30ddca14e0180b501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a91fc7e77ba226b15008e2bcdc54e196b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LEFT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a33cf98bc81668fe9dc4eae0f5c41780b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_RIGHT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a7ac285c92ea3048e5ed006af3d453b42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR_MIX</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a0358f0cc0ad00b1551e0f7387b112e3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_PcmFormat</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gac631266018b8f5df7df1e52f65c2757f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_BLOCK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757faa072981204cf2b0d1cdddce4d9644154</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757fa12f80fc0827105d6dc1df1dda485d161</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_EncMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga1d8af2cbae15bc609badbb328ab3a08c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_CBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08ca422efb88eb135a5212bfa6b3600c35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_VBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08caf311198449fe7e6c2e20f79d66b7a0e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgdec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iimgdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGDEC_Obj</class>
    <class kind="struct">IIMGDEC_Params</class>
    <class kind="struct">IIMGDEC_DynamicParams</class>
    <class kind="struct">IIMGDEC_InArgs</class>
    <class kind="struct">IIMGDEC_Status</class>
    <class kind="struct">IIMGDEC_OutArgs</class>
    <class kind="struct">IIMGDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga399a3c00c3d9181c9b84a86549c76344</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4c2d7f1c15e1bfb70a61ae987979ad3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf11d65f2c57f70bfa994221f201fe483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gac0a3c1ac74db21cce563ac1af0dcdcf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj *</type>
      <name>IIMGDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaafcce966766ae1ec2ba860294450603c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6d702c2802e8827926120bfeef5de0ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgdec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iimgdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGDEC1_Obj</class>
    <class kind="struct">IIMGDEC1_Params</class>
    <class kind="struct">IIMGDEC1_DynamicParams</class>
    <class kind="struct">IIMGDEC1_InArgs</class>
    <class kind="struct">IIMGDEC1_Status</class>
    <class kind="struct">IIMGDEC1_OutArgs</class>
    <class kind="struct">IIMGDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga71491761ce7894192d0953f62e87922e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga31103bf98612d017b2f5c11cc14ac842</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga184dc94b44712d77629d785cefe1398e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj *</type>
      <name>IIMGDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8b9b9364f2c4232397b36890618b250e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7bf45653f5c04d9407d13394663a896c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iimgenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGENC_Obj</class>
    <class kind="struct">IIMGENC_Params</class>
    <class kind="struct">IIMGENC_DynamicParams</class>
    <class kind="struct">IIMGENC_InArgs</class>
    <class kind="struct">IIMGENC_Status</class>
    <class kind="struct">IIMGENC_OutArgs</class>
    <class kind="struct">IIMGENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gac529fc95d138993ea754d7ec6018a76c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga784e32991d906518f37e7a5146f5bf13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga827d911bc03c756096d03677ecef5f39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga04b132637a7c8ee29f0738fce76fed32</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj *</type>
      <name>IIMGENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58729c682862e2e74a9b2abb916f4b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabe17217ceb746ff5b0e564a6f3dafa36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iimgenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iimgenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IIMGENC1_Obj</class>
    <class kind="struct">IIMGENC1_Params</class>
    <class kind="struct">IIMGENC1_DynamicParams</class>
    <class kind="struct">IIMGENC1_InArgs</class>
    <class kind="struct">IIMGENC1_Status</class>
    <class kind="struct">IIMGENC1_OutArgs</class>
    <class kind="struct">IIMGENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9397909ae52d3bb547e18fd8719c333f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga28ded0a8bcf744f7ba289e9b6ae576ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad065eddb703a62fa12207544e8546f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj *</type>
      <name>IIMGENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga93fe674dab191daf45489f5bf84134fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga391d9f36711efa2b355c14a03af7abf8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>imgdec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image/</path>
    <filename>imgdec_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iimgdec_8h" name="iimgdec.h" local="no" imported="no">ti/xdais/dm/iimgdec.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IIMGDEC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_EOK</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga18265bf93b5508740ac1b3d546f1cb75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_EFAIL</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2f4ee615a65c5dcc72cfe57997426723</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_ERUNTIME</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gadd2ba1d0e893b1b5f5b1e933ad492675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_ETIMEOUT</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2c60d166796461a4e9ee4ef554419fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_FOREVER</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga8b51e0e9bfa3b6aee4f4d7bf9caf36a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_Status</type>
      <name>IMGDEC_Status</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga58ebb7923343f50683714a7463933e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGDEC_Handle</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga0768d267cc9be1cda691a0fae30655a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Params</type>
      <name>IMGDEC_Params</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga60f2242db982a2a69f1c025bf4f708e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_InArgs</type>
      <name>IMGDEC_InArgs</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gae0939dc64e3ea2514c48a8af19d9a3f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_OutArgs</type>
      <name>IMGDEC_OutArgs</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf78b37f058a09beebb599bc4ead7441e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_Cmd</type>
      <name>IMGDEC_Cmd</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga89ac4c1fae57006371ee38bc87a00be7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_DynamicParams</type>
      <name>IMGDEC_DynamicParams</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga1610026234cd8732f5c3664ea77371ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>IMGDEC_Handle</type>
      <name>IMGDEC_create</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga7bf438523b872178bb45c124f831c551</anchor>
      <arglist>(Engine_Handle e, String name, IMGDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC_process</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga80cec6e31f11193684534228890443c1</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC_control</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga361f5d57077f48fc9741834baf839e15</anchor>
      <arglist>(IMGDEC_Handle handle, IMGDEC_Cmd id, IMGDEC_DynamicParams *params, IMGDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGDEC_delete</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4a99768e5cf0e3e1009610c1129980ca</anchor>
      <arglist>(IMGDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC_processAsync</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gaed139e4f01252d64cd455180bf77fff4</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC_processWait</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gad6c4ce38e17925aa2ef88d0840b5b6ae</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>imgdec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image1/</path>
    <filename>imgdec1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iimgdec1_8h" name="iimgdec1.h" local="no" imported="no">ti/xdais/dm/iimgdec1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IIMGDEC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gadad666bc5dc5da3d800148989639327e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga1e275de814f6d8642258c68a3136b75e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga90b7f2c50ad51a88787996590fa77ef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8805b253e0336884dca9e56ddd530634</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gab30e34559cc8849c8effbe6ec5f541e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gacf60594a88881713b025cf2d9fc22c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Params</type>
      <name>IMGDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga6cc479787ad5fbd119eaebdec9ebc333</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_InArgs</type>
      <name>IMGDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gada90b2b2359f429e8eef0d3a5ed66715</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_OutArgs</type>
      <name>IMGDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabf54904c6c64d848e8a325e2456e6c22</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Cmd</type>
      <name>IMGDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga6f8a6dde7d6d121eadb391ad2b18e97e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_DynamicParams</type>
      <name>IMGDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga59288a5b06a9770227c78de934e525b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Status</type>
      <name>IMGDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gac9bc559efa5ef1fcddd0cc4c3ce6d2fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga83c6818a0b02f0ca06115d4258c6ede9</anchor>
      <arglist>(IMGDEC1_Handle handle, IMGDEC1_Cmd id, IMGDEC1_DynamicParams *params, IMGDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IMGDEC1_Handle</type>
      <name>IMGDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga66558eda5ac60a94c643533277c15d79</anchor>
      <arglist>(Engine_Handle e, String name, IMGDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga97e6f62e2348dfc73fd720e26a0092f5</anchor>
      <arglist>(IMGDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga320bcaf531f5561c3a27a60ad7136b58</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga21b9f33a3da90adc8f896ad8edbc78b1</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabfc0a347e34e33701dc36f32da2d39fc</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>imgenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image/</path>
    <filename>imgenc_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iimgenc_8h" name="iimgenc.h" local="no" imported="no">ti/xdais/dm/iimgenc.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IIMGENC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_EOK</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga3fddab07429ce18f219c808a9636c1c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_EFAIL</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga1035fa201d367beaa01171d3702d3c89</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_ERUNTIME</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga7468e67ebca1c5089a98176081fe3a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_ETIMEOUT</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga4bc59bd8632e0441adfe8026aedff4c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_FOREVER</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gacadfe8b4b15c7d2ed88b7a78f6b8581f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_Status</type>
      <name>IMGENC_Status</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gae1cd05f2a14905e9f0578c23954addf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGENC_Handle</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga13eca575480879d3df31e1a2d588b43a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Params</type>
      <name>IMGENC_Params</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga20b07e44e01e327926ea8c41f1876729</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_InArgs</type>
      <name>IMGENC_InArgs</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gac3b9b18dbb0a8cc69dbfcf66b2ac886d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_OutArgs</type>
      <name>IMGENC_OutArgs</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga0412ae052b70d1e648e9cc55e6edb5f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_Cmd</type>
      <name>IMGENC_Cmd</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gaedbc4d6f51636441aefd18ee97169fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_DynamicParams</type>
      <name>IMGENC_DynamicParams</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gab301d74ca14ca7db405477ca3f0e24ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>IMGENC_Handle</type>
      <name>IMGENC_create</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga9628ee04bd5ef12f6972dc1708237677</anchor>
      <arglist>(Engine_Handle e, String name, IMGENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC_process</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gae4bb1eb7c6c7625da250eeafab35ff06</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGENC_InArgs *inArgs, IMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC_control</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga5183342c7640653294da59dc59041212</anchor>
      <arglist>(IMGENC_Handle handle, IMGENC_Cmd id, IMGENC_DynamicParams *params, IMGENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGENC_delete</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga92c2bcf19de0ae718d0229de853d85c5</anchor>
      <arglist>(IMGENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC_processAsync</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga3f20ac89181a99022e282c24bd0c4a57</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC_processWait</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gab123ef1a678725fafd78bc68dd620f14</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>imgenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image1/</path>
    <filename>imgenc1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iimgenc1_8h" name="iimgenc1.h" local="no" imported="no">ti/xdais/dm/iimgenc1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IIMGENC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga57670039c8686c8516f5cadc88e41cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gac7c0b09a9f97584f1f5670297bc99505</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae0706d2612934f3195b096f2bfe8be83</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga8ba470948d353c973c2c44c0fa016040</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga0e40a27ad4939058690c0be561c5d7b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga25441483c5175bef9cc003ccb591a0f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Params</type>
      <name>IMGENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9c6dca09ddb4457155309d9259f195f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_InArgs</type>
      <name>IMGENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga1d82fa42f9a18951bcb217bf90daad30</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_OutArgs</type>
      <name>IMGENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gafd2a75a9ae2c88d7771c146816545dc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_Cmd</type>
      <name>IMGENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga70cb858c6f18680aae37732b1efb4ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_DynamicParams</type>
      <name>IMGENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad7fae9fdd89a9d45701cc449d92e0dc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_Status</type>
      <name>IMGENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9c88d92cdf6078a11f7dfe151eeb0cc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC1_control</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga5f7473a42611fa3527c9293a31a90ca6</anchor>
      <arglist>(IMGENC1_Handle handle, IMGENC1_Cmd id, IMGENC1_DynamicParams *params, IMGENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IMGENC1_Handle</type>
      <name>IMGENC1_create</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae662096fff942c48b7cb9632c462365c</anchor>
      <arglist>(Engine_Handle e, String name, IMGENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga929b104c6d4aae0f1002c0c92c0b0abb</anchor>
      <arglist>(IMGENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC1_process</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gacb34e6495073f40e06282bb17b394e06</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGENC1_InArgs *inArgs, IMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gac997094b38bd65e1bfcf9f9af0f515f4</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga933289ef04af9d63a903edf11eeca274</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech_8h</filename>
    <member kind="enumeration">
      <name>ISPEECH_VoiceMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ga2a5ad3bdafe1e87e2aece51b52700694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_VOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694aabfd422047de38c75ff1caf9f22c7ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_UNVOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694a980404cd1fc1ad41d588319dbe3ed14e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH_CompoundLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gaed9882c92cb24a565d63fb157a3bc0c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a8913b9e1f47a5e7ab97578c12a115a06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a254d39814c846c8f5574226162efb458</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a1edb2eb2e360b5292385c671181cfafd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1_8h</filename>
    <member kind="enumeration">
      <name>ISPEECH1_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga89ae95d0bce445642cc16c57c0d0968b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968ba87608e5344ca37912234e93b7da59630</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968baa933263447c238bac7df6321e0a11694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968bab4fa5328474e29188aee74797c414aec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_PostFilter</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gac1c8b96d345c0fe4220cdc18669223ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca6f4c302f3c9af56f64806d0861abdd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223acac8e86af79d47c31e04829919bd972705</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca37e583ca98bc612bd7dd9c5c451b3cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_VADFlag</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga6a40ba3d92ffc5b64a9987f870f57f9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa4d73bb62c3d482112334d7d84cc3cce4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aaa11a5dcd1ae9d5e026cc83cfbb330919</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa7e66df60583013e51ba279139d13e0b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_amr.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__amr_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ga566156cfc46f87e73de6bba8eba536c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_4P75</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a99fc4c000b12f09fdcad255694d96d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P15</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a5e8739090838a47dded4ce9c617b2446</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P9</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a633eb6129d753bd00318c91d5c00647d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_6P7</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a61ffd17b289e507380d69e1eca1c2142</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P4</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a45de32cc24a76e2a16bb7f9eecdccb48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P95</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a3d3312de4a395a0a154c13043e6be957</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_10P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a7ca5663dc228a321dff14edaa5887aa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_12P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9af65cf724c197d3cad7dd932c44e7cba1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a4943c07dd5924193d6a0a8ce7986c295</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaf6d3e11e5b975770afd11caadcfd8d20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_PRIMARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20ab414f0b43b46c6407188ab18f07abcd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_SECONDARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a06effe2e6cda9dce3ce1773be4a941ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a055d66e70f1130f7dd8eab2f05e01e88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaeecf736d60bd00c5ac86924b1404ad90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af79b43d1eb83abaa5510928b71a4abe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a387c71ba08310d9668dae3883fe3ec28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af1bbe3a63ca9d6f595b83fa6b91a424c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a71f0423b70c34ca2afc083e5a62585e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90aa00c9bc982212f0c55d9f1477bb62ded</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gabcb3c4ae9c054b69eabd71bde775d86f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86faf55aa3a28417e1d0da82b546a9b1789d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa35a83e8d85620ee0316880049aef8078</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa4789cd0dfd81240681e04f81d7ead9fd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_evrc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__evrc_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gac0650f1ca8b6e4b6770c038653594633</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a9265da05d970eef081d3dd7ce9dbd4be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633aea1b311ebb57531b23d73857aca828d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a7805bfa6106590db880f7bf892c680d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ga84ecf83f56e51c826bda7095a90b989c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca38d82305bbfabe8919932618e2fdbae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989cae7259cf80bda232f425379647111b048</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca602b2e9a9e7a1dbaaeafa889230811ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca1d60ffd9d5228746176eff0117c948fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gafe2167d2bb6dc8269af94931fdedc9f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ae8264ae8cb01ccb0953e29e0c3b21cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a8fc2dd52641a64b43d8034b4c0acd1c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a044dbd71700d328377606f5285bdde2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a7d31d7179ec70e3e28954a6d989d688a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a5920a92eccc31bc941e54ab46a84a80b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ad54aeffbd74c41175c7c3f7d427ad144</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g723.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g723_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G723_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga3a60101c5d140281222eac55ceff3da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_5P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a25ef1e08d5e98120471e2c1526c27d2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_6P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a1e8c817ed1c0bdb7fb55444d6e009353</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a27554cc9a39b340e0ecd8103719dbffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G723_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga6030020ca3fe69e0d0aaf01728097eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaf62d62d2826cc658130274930660ebb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaae41fd25b630c16118a4ffd24276a990</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaea889aecb01aca1afc4152f95a8616c147</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_g726.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__g726_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_G726_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga5842c3df33b0aec82142cf1fd3ece12e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_16</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ead390f395f226d55baf122302237cdf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eab03a295d41900a44a9c94f3c94baceb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea769ceb35bd641aac0e5531f1641285ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_40</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea8548d58b48b1e6ed42f18024d4793a0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eac2a351d221bfea5d27b09134cb59e89f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gaa397870da5177152ea1b53fe9e3b6265</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ad0d2189fda7ed821f96577af3b5ba01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ada1a67c0602e35ec5c10fba0044d6eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a1177bc10761f7968fb1787cf2c5bf599</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a386b0d978c9c63729567540b953c7105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga889c3788d8981cec15df6971d29306ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaadc717daa84241ac0f3964a2e5a0f564a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_RTPSPECIAL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa3e3a96fa9418c89e58ee8dcd75868ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa9cfac3209bb22296fa011e0875b37d27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_pcm.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__pcm_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_PCM_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>ga88faff6d78d80fbb0d3712642a16e1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea9b50f6c66d7d1250dcede6c3076bdd45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deaee6ede174249a7ee7b67daccf7437037</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deac8a7be49178242066ee82b6800905614</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea5b651f269b71e3d9cfa3fe8e6d494957</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_smv.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__smv_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gab60bcb3149344cd20bc1d9d1696a208d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da499e6a288509dc326fa6b2a3a211d092</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da5adad45c8630058c96bdafdb030931f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208dab44c90dd52dc8fa6cf0c528ffd540e77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da39b444aeb37c32f83aee67c415679c04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gafb1b4ac5540a4d13c730aaf88dc023be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea1c29ab48b1ef4af475eb3e95c3e99613</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea6b4ba999b85279488c3db4cae5aee7f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea7db43399885c4cf5f1d122913fb1f0ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gad14fd77adfb92f65088ef0b2e6affebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebdafe82060bfabefca805a51b04c4381003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda0105f17fb6d97417b56dccc9fde3c73e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda34cd37f4c8438ade28d24ba1bf3d401b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda3bbed1bf636d4ccbca35915ca01cff7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DTMFMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga91d61a3a68a62af8f73afb871f1d0d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eabb2bce58703d51269e15c8a9bbbcc11f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5ea325b10e0073a2d82e2d272b2dba7149e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eafa3d0d05dcad59534119e6d6f60326a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga9edbd6e156d41f8673e3c26841e4d1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa2c0c4bae0b4e38ec003b221f01bc6c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_HALFRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfae9e8887b1b23fc33614aab40523f7f5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_FULLRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa02c442553dc94438337a7f0b5217d587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa94de3a5a683830f5e91b1f488a7598d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gae79f94ea770cb63e97b6b08e7021a7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a605f932ca11a86e867b24a87f7c2cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a0a3ab57cb83cc3b78664e5f8ee9dc0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a30a76e29dc26f9d6b58461669bbc485f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a3013d7d320c975226bb2785ce39ca852</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a764290efa25fc2f82cba26bed3b788ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a02765b3d59b321e563dcfb2aefdeb8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a04f904d973435832277167859b16647b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ispeech1_wbamr.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ispeech1__wbamr_8h</filename>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga8561c34af4f9307ee99eec22b9023da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a0fefa4be1b4fb97d523329d3bbc3d42e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a54c89d0a6ae8cb89e5097e39a5e4b06d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a67d42cd4150cd7c05378bc1960a92375</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7acc83cc0d4a577f3f93025e2eff1e2bb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a568e1ddb1a8b6fff6d9c018c9ac3c7a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga60889eeb323f514221f3623e9f749716</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_6P60</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a7821bf03d8f659a4835541eb711741e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_8P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a5109ab789372f28d132350cef02cbe70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_12P65</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a6cf6726fa2af44d0362bebdbbb05b642</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_14P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a823b5ea1854bf86a1534e790e1410b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_15P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a82efce13fac3031b423f01efa1e00969</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_18P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ab306cb8177634d2dadd04c0ab3aadb32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_19P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716abf4b551e950f3dca496dd1781d7d8811</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P05</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716adc1493eee4d5e1df49cade040980d720</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a45f6d3b08c97d14e0e4017c9328bc965</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ac599e0494b8cbc4788a5abf95232d87f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphdec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>isphdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech_8h" name="ispeech.h" local="yes" imported="no">ispeech.h</includes>
    <class kind="struct">ISPHDEC_Obj</class>
    <class kind="struct">ISPHDEC_Params</class>
    <class kind="struct">ISPHDEC_DynamicParams</class>
    <class kind="struct">ISPHDEC_InArgs</class>
    <class kind="struct">ISPHDEC_Status</class>
    <class kind="struct">ISPHDEC_OutArgs</class>
    <class kind="struct">ISPHDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga1f604442aeef3232e6acc17de9ab51be</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga59bee2fd448023ee04185aaf874cfb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga6f7990140490a16e025ffc1d670503a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga48b7104fbe8c5c6cbe2d17b7725e278b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj *</type>
      <name>ISPHDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga31722647a0a3b99c36ef57af89d1351a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga73cebce9e1ccbbb0afbb14a4f984a94e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphdec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>isphdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <class kind="struct">ISPHDEC1_Obj</class>
    <class kind="struct">ISPHDEC1_Params</class>
    <class kind="struct">ISPHDEC1_DynamicParams</class>
    <class kind="struct">ISPHDEC1_InArgs</class>
    <class kind="struct">ISPHDEC1_Status</class>
    <class kind="struct">ISPHDEC1_OutArgs</class>
    <class kind="struct">ISPHDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga87514ee862e0b5a35fcf460a65277a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4d2a2279596c72d1d505a94504af9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga712c57b5a16ed53f484260f8ea48c1ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj *</type>
      <name>ISPHDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga65c6e2d620b2b46594453ed84ded159f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaef02eb7c18d91b4d4183284c0c4c1d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHDEC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga80a8f44022a98fb899a102310489ebf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHGOOD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a1813dc29630e6fd7c6054187077f1b0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDUPDATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a10c27d875c65247b78a99e1d28916dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a46a224a6fd50ee1f3fe602c64759c158</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHLOST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ad7f3cff31625d40f310aaf0a575c1117</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_DEGRADED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9abce8dcb8ad83419dc8225b66d2a36c84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ab576985e54ff855753483500e17362ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDFIRST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a6bcbda5d5df41d58f5a5034fdabffed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDBAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a4cf9a9b2ba2919adf36aac69de785623</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_ONSET</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a0a642d1a2df6645d04a98d198b42a5b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>isphenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech_8h" name="ispeech.h" local="yes" imported="no">ispeech.h</includes>
    <class kind="struct">ISPHENC_Obj</class>
    <class kind="struct">ISPHENC_Params</class>
    <class kind="struct">ISPHENC_DynamicParams</class>
    <class kind="struct">ISPHENC_InArgs</class>
    <class kind="struct">ISPHENC_Status</class>
    <class kind="struct">ISPHENC_OutArgs</class>
    <class kind="struct">ISPHENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaa70981aaff27acca8dc15214ad0538ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga7e16b5ce02a4ae9c232445e1b1628f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gac472f9baf3f8de53cfef7d83a05df2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga3769ec58a3fb188995557ab5f4986a0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj *</type>
      <name>ISPHENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga53d4faeb65284507a1eab034036a11ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga835dc5261cc96bd0c6a77c1b33f5f197</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>isphenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>isphenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ispeech1_8h" name="ispeech1.h" local="yes" imported="no">ispeech1.h</includes>
    <class kind="struct">ISPHENC1_Obj</class>
    <class kind="struct">ISPHENC1_Params</class>
    <class kind="struct">ISPHENC1_DynamicParams</class>
    <class kind="struct">ISPHENC1_InArgs</class>
    <class kind="struct">ISPHENC1_Status</class>
    <class kind="struct">ISPHENC1_OutArgs</class>
    <class kind="struct">ISPHENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga332d5aa164c31b5681b2cea91d7e5016</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga22ade7510d7d35abb25a60b64f44a92d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8f31ee15e0081314b41914efc29c5a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_ENOOUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa82f51e92fce79e8c507771c443b3e35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj *</type>
      <name>ISPHENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga995e9ed220499520c23c0df118d7acd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga16523cd9d058f54acb8f5d1bd4bd5d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHENC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e6571f54c1264844aa2c0e05119a624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SPEECH</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624ae24818a9a9b1a23146162bb950ab035a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SIDFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624aa8c57b4e299ff4038b40a5911eff281d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624a6e2c23204ce4ae3dd2001aa610644638</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>iuniversal.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>iuniversal_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IUNIVERSAL_Obj</class>
    <class kind="struct">IUNIVERSAL_Params</class>
    <class kind="struct">IUNIVERSAL_DynamicParams</class>
    <class kind="struct">IUNIVERSAL_InArgs</class>
    <class kind="struct">IUNIVERSAL_Status</class>
    <class kind="struct">IUNIVERSAL_OutArgs</class>
    <class kind="struct">IUNIVERSAL_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga27f56f76d4fd15aa0d7e0ebbcb861d4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gad0ebbb98143ab6995c1268efa4cbf150</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gacb40d81bebf31e7de2267d6cb9bde3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj *</type>
      <name>IUNIVERSAL_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa47732c807c80b94d7f29cf72d9ed694</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IUNIVERSAL_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga17756fe87be378872a1647a668f18c9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividanalytics.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividanalytics_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <class kind="struct">IVIDANALYTICS_Grid</class>
    <class kind="struct">IVIDANALYTICS_Rule</class>
    <class kind="struct">IVIDANALYTICS_Obj</class>
    <class kind="struct">IVIDANALYTICS_Params</class>
    <class kind="struct">IVIDANALYTICS_DynamicParams</class>
    <class kind="struct">IVIDANALYTICS_InArgs</class>
    <class kind="struct">IVIDANALYTICS_Status</class>
    <class kind="struct">IVIDANALYTICS_OutArgs</class>
    <class kind="struct">IVIDANALYTICS_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaf9760765b216cdbc5079be6e1904b795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac314c2ce1b08297ccfbf0c63dc3a257c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaebc9260d46c5e53d35bb4f5f100b96ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_SETRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3d56d0f1a5afc78401314d4fdee63dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_CLEARRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga44579981d799141f6e0368acf999b8e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXTARGETS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade504e11b8b0bc9e3925640b2cafebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXEVENTS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa71cddcd1d8b054c48f9966866e386b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj *</type>
      <name>IVIDANALYTICS_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga26ad8d51394ef852e42cc1c4948de0eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5be3d2530a181c9826dc4c3322344132</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_AnalysisMask</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga4a8b524c62f02622465884156f2c6f59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_MOTIONDETECT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59a3cad03f6d20ecbdc0103df4e73101e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTRACKING</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59ad6da9e357c2c7721f04b1ff5beb38929</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59af48becd353153ab4285b4305d3467624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ObjectType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga40e54ed88eb97360b4ca8f244c2b9f62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_VEHICLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad9daa80daa5e20d4c010d577a7347918</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_HUMAN</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad82eb960014d7ede011678c5705ee1ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ab6cd25f42da6d9e7e43ebb4ce272cf97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ActionType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga47e8c8886c5d35981380c922db1eeab4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_LOITER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aba5736e40d9f5ab0ff2590d66e04edc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_ENTER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a86e2c5b11a0e4c20d245cb6de0cf8bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_EXIT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4af0f133918f8b9575ca32e05f512270a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_APPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a681d3cbb139a67f813899f0be3250f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_DISAPPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a570191d5b93ea4345fb5bcb91f3a4d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSL2R</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a25a21e42fece6687a27205a828e025e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSR2L</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aa4df30a99741c60e039d8042476922c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSU2D</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a82b0a4cbd8efa23126decf532abcf6e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSD2U</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a899876b69418a4b7187e73a1fd22e0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a20b606cf024b3812694d53e0f9985cde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ViewState</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gab02bfb6a7b2a76eac00f1bb7d3801662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a42c1e0003605067a4def8cfd4c061dba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_GOOD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a093b1e31c7bb032707492cfe72cd8fe8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividdec_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC_Obj</class>
    <class kind="struct">IVIDDEC_Params</class>
    <class kind="struct">IVIDDEC_DynamicParams</class>
    <class kind="struct">IVIDDEC_InArgs</class>
    <class kind="struct">IVIDDEC_Status</class>
    <class kind="struct">IVIDDEC_OutArgs</class>
    <class kind="struct">IVIDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gafa63f96dc4a5430e21a8454a609fe205</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3fc5e8b896808e13dc4a1dd037592c61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f3f0d74b7b4895adc3601998895b930</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3ff96fb69baef4d04b31682234957de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj *</type>
      <name>IVIDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gabc249717018b892fafca9425887b7464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7f8d05603824403adb994fe59d55bdcd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividdec1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC1_Obj</class>
    <class kind="struct">IVIDDEC1_Params</class>
    <class kind="struct">IVIDDEC1_DynamicParams</class>
    <class kind="struct">IVIDDEC1_InArgs</class>
    <class kind="struct">IVIDDEC1_Status</class>
    <class kind="struct">IVIDDEC1_OutArgs</class>
    <class kind="struct">IVIDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaee746b34bc5327d7755c36e9dbb93f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gac76d0185e99e4dfb7d33f8b06d73a731</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga8c35fdf3e5022078dfee9064ac08f52a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_FREE_BUFF_SIZE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9fd4bffd14decc067ecf3f2c486605e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj *</type>
      <name>IVIDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga3470ccaa78e2f267e1b8e08c7ae25455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88cf5de26dfa5e05400b2d6e25ea027d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC1_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga499b0864c81e20998f743b9e834e10c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a9fb1a3543d4c48a7c5a7cf9242058746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a3a281632bb399cb0c73a18ebff327706</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6aebd67fc7b931e0796cfa9a970137b12a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividdec2.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividdec2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDDEC2_Obj</class>
    <class kind="struct">IVIDDEC2_Params</class>
    <class kind="struct">IVIDDEC2_DynamicParams</class>
    <class kind="struct">IVIDDEC2_InArgs</class>
    <class kind="struct">IVIDDEC2_Status</class>
    <class kind="struct">IVIDDEC2_OutArgs</class>
    <class kind="struct">IVIDDEC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaf8c9523a27942aa46eba097398a0e49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac1f0ebc291c92f796a5144fa57f7390f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7c8386cbcd58bcb8a16e15df6587f3f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gafa7a5979f7945ff9ce5822c8f5fa57d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj *</type>
      <name>IVIDDEC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gab044a3dd5967ff04c487062ed0586c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8b9180923c067cbb47115d18189501c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC2_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga31f21bf0ec796b5506cd8a0f0cf7710f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa4dc184c19c62190e5f933e46e5bccc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa33ea07222ede0a10cb27bad4b9db445d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa3599bb4a0d320e3e36d2aa49a7ae79e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>split/ividdec2.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/split/</path>
    <filename>split_2ividdec2_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <class kind="struct">IVIDDEC2FRONT_Obj</class>
    <class kind="struct">IVIDDEC2BACK_Obj</class>
    <class kind="struct">IVIDDEC2FRONT_Status</class>
    <class kind="struct">IVIDDEC2FRONT_OutArgs</class>
    <class kind="struct">IVIDDEC2FRONT_Fxns</class>
    <class kind="struct">IVIDDEC2BACK_Fxns</class>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj *</type>
      <name>IVIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaa273ba82e5f6d894000c4031d905776</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj *</type>
      <name>IVIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8aedc496483d9ad90fb544045934648d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividenc_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDENC_Obj</class>
    <class kind="struct">IVIDENC_Params</class>
    <class kind="struct">IVIDENC_DynamicParams</class>
    <class kind="struct">IVIDENC_InArgs</class>
    <class kind="struct">IVIDENC_Status</class>
    <class kind="struct">IVIDENC_OutArgs</class>
    <class kind="struct">IVIDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaeba527be430e1584897bc410ef06e08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf31926403a1beba354092c33e6f8f41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf0d8e925b556bc7d992afb7dc9005fe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf08f3e2a75c1e39a184835d0683ca88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj *</type>
      <name>IVIDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe560b65239e58d0a48897db58ee33f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga13eaed2bcde87e35269eed69590e2313</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividenc1_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDENC1_Obj</class>
    <class kind="struct">IVIDENC1_Params</class>
    <class kind="struct">IVIDENC1_DynamicParams</class>
    <class kind="struct">IVIDENC1_InArgs</class>
    <class kind="struct">IVIDENC1_Status</class>
    <class kind="struct">IVIDENC1_OutArgs</class>
    <class kind="struct">IVIDENC1_MbData</class>
    <class kind="struct">IVIDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf7b49aed126ab846bbcff9bb2d481533</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8022d457cb04187a3b1a055eaa2d1629</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1623748edce151d19caed068981773f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj *</type>
      <name>IVIDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga953dc9cc5ece87d8b371bd2adbb5082f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2654e133ba490dec6e8dfa56d1b633ef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ivideo.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ivideo_8h</filename>
    <class kind="struct">IVIDEO_BufDesc</class>
    <class kind="struct">IVIDEO1_BufDescIn</class>
    <class kind="struct">IVIDEO1_BufDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_YUV_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6f88ee11da1a2397e9ac263ce3cdd537</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameSkip</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6533d232a1c479dd185945e9c10c2665</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NO_SKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a8089c337b034434f8d53d279022272f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_P</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a767894b6dfb8639c2298f2d31e5fee51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_B</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a04cadb8d98980be81a2a8a3fdc0372fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_I</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a551353a345ce3929adcff79aa741724b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a1b9f609f763ae7d8b36262986bcf54a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad111bef6602a59d8998ba5b4adbce87b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_PB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a2e82d4e64d50c7fae14a1ef6720d3588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IPB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad9ffc660a588536746fbdb3d8b5b4f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IDR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a98a74bb46bd05f43c4db0ae8f8f66eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a0f0844d71eeb68ce22bc9d9f840d93f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7ad672ade5d380f42e0cfcfb2b38b6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfab4b11cfbf563ce054e55fa482fb67f79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac2b378280d95551841dddec15fad1d43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad788ad7b0f7a8517de35c5cd0aefc28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa7dd078d4f4f309da2e73494ddd01f2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad7a86650a7f248f11133e52da2cb3e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_II_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3be138a2faa58c0d85e2ae533526af79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa40d74846bed523f78efbd61e42736dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9cc0602312932db087a8e89b807c59a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa394be4bc1774efef87892bcb6387d4d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9ae131687a2c620b50be3cb9bdf9ef69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3eb025061d65605fa2613a1219203662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa99b48bce066d122f86f67d281709c970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf6d75d28ac6582ed372ca9dcffd7a31e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaa8dad288ba397bafe98f9d3dcda06efd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac0c3748111b37e34c2652e311b367f18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa068cd4d6a1d797d1b3eba96255c64b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac34147d75fecab15f7692ff0be138df6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf9c5b520fe2612d88725de4bc1224d28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAMETYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa05a31e040d22bea216e10f2ce8cd6472</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ContentType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gac397e10110dd59e8266cf5831c68f44f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_NA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa61cc12c39b88ba4c10d51a9d9393405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa6b7ae345e50ccd4c5589efd85e18194e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa36a57cca2ad3435c423515e78dd7d1ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa53e2513e3f2b155abb3bb707ff2fbd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa399d126875549ace3806efddcfc45ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_TOPFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa74d16186e87100648b97eae32e72d90c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_BOTTOMFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa980c869708ff1245fd7f1859515da631</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa35c626f7476288db897680bc43d92243</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_RateControlPreset</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga33dcd88e11f7c1a614c37729e6b99592</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_LOW_DELAY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592aee9478fdaa09a124e84a5f52373213f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_STORAGE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ad38ab0817089a19a753e2ca6b6e5d165</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TWOPASS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abf4ba1f0aff97d13bf49af0d574ad040</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ae222e2b721a93726945d9b563631fda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592a8e5fffe1c7bb0d34fd55b8820cfdb7e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RATECONTROLPRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abafd796f46fc51340a58dadf2f725e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_SkipMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga911b2a9c63a7a8c16b86ae2b43acb609</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ENCODED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a899d064f2315fc727725330cec39a441</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_SKIPPED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a728d909773039ecb6c8481ce587ff948</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIPMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609ac81722aae2d59cad8cb864dc68c81d23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OutputFrameStatus</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7d713a3e9b5adacb039de4419d5527d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4acb9c873639468d10824089bf2c196884</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOTAVAILABLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a3884312affd02cbb477b0bcf9ffa4a8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4ae22471e0df0ebdbc17ad840deec9ba24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_OUTPUTFRAMESTATUS_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a4bcc02f48972d600ec61e933133b4587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_PictureType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga90dd6a0a4863fcc6d3d523eda8a78ed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aed1dec6b10bca143d42b83d26218d26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a85a519797900b0bbbc5007c14e6bab37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a70166338c9fab34bb0fc6534a0890ea3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aa8b180d5b01bb100e326d261684ba7f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PICTURE_TYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a5373e837eb3564b15e0a0203ecdb503f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_Format</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4aeb19b8e5cc42c49fc8820fc4e1b4aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b8d27c8e2c977e98780b30be68b4553</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1d3f020030f6624621f546640cd97195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa77ef7b91a48b372bb8fd6104ba4c53d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8cd7c6245521d4003ae12244eb8616e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa58cce125a57189f5ad23250b0ea41dce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4ASP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa35e77ca8ec953280e5615eb9e799211b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264BP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaab62f85b5ad0f3716733800202de13725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa65745c33e161b9e725dd1093d6afb535</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa204e56351a5162ac38b3abfe5456ab87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaabb227ae9ca9aea83e804a2afc9137e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa673d0eb07f8c957878812eebe0074b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1AP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaadf58ee1effdc2c92756355575b471123</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ividtranscode.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>ividtranscode_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <includes id="xdm_8h" name="xdm.h" local="yes" imported="no">xdm.h</includes>
    <includes id="ivideo_8h" name="ivideo.h" local="yes" imported="no">ivideo.h</includes>
    <class kind="struct">IVIDTRANSCODE_Obj</class>
    <class kind="struct">IVIDTRANSCODE_Params</class>
    <class kind="struct">IVIDTRANSCODE_DynamicParams</class>
    <class kind="struct">IVIDTRANSCODE_InArgs</class>
    <class kind="struct">IVIDTRANSCODE_Status</class>
    <class kind="struct">IVIDTRANSCODE_OutArgs</class>
    <class kind="struct">IVIDTRANSCODE_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga69d74b9dad25f19d864771f9d81a9a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga29ec01f0e1dea7abff118a9cf8792885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf6e122d808cecd873a7f51e34c2fb4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_MAXOUTSTREAMS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9b9cc80049e4cebea89e7c4cf58d426c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj *</type>
      <name>IVIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga049f5b53ee2c04135a1ff19afbc215c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gab5d20cf8d615294c7912796b79f85f5f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>ladclient.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/dsplink/utils/ladclient/</path>
    <filename>ladclient_8h</filename>
    <class kind="struct">LAD_DspStatus</class>
    <member kind="define">
      <type>#define</type>
      <name>LAD_MAXLENGTHIMAGENAME</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga8e07e54d7aea12d190555cf31db17c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LAD_MAXLENGTHCONFIGNAME</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga901a4242cb9df3d3c2c302f4d9c7e6e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uns</type>
      <name>LAD_ClientHandle</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gab2c7f70765d4bd228dab4533b09b71e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>LAD_Status</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga66608549d1df270be82121e78bedfda1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_SUCCESS</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a5802b07b46745ac8f39998db29cc2249</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_FAILURE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a1319915bffee06594ea9ba14b391e331</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_INVALIDARG</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a87a9a89db556994e101dba2970d7364c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_ACCESSDENIED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1aabd0ac5be9c88df2e212f56969fc1568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_ALREADYRUNNING</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1aaf4de0b0d821d54271116e7bfd9940ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STILLRUNNING</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1ab3bb8044e7eea1d1edcb515268b6f3cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_IOFAILURE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a2a42d4f645ae6a4d5169da7d05333124</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_NOTCONNECTED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a9d549f85bd6bf35bd8cd8631257af09f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_INVALIDVERSION</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a139300fdb548633dd734a3b9edafe9f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>LAD_DspState</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gaa4571d04b2df6dbc63ef29617272e22a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_UNKNOWN</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa66542229d94a84789da0b2a77b082124</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_SETUP</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa686d5fffa5c19ae9252f25fb7b73ebb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_LOADED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aafc9b72be215e0669435e6ab62961c2eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STARTED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa68ab6fef84749e86c15294c1ca68f051</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STOPPED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa22795295bdd8124ac776b031d568c5ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_IDLE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aadd33b67055b31bf478ca9c0ab654ed08</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_RESET</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa1cc66b69fb539f224d959d49c5bfc792</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_UNAVAILABLE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aac01999184a3b1c65950843831a271b60</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_connect</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga1296ebdb60b7bba19643006635075af5</anchor>
      <arglist>(LAD_ClientHandle *handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_disconnect</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gababa518d4fe889e45400f80b4855802e</anchor>
      <arglist>(LAD_ClientHandle handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_getDspStatus</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gafb7216195e4cf5f94f99f171f75e74e8</anchor>
      <arglist>(LAD_ClientHandle handle, Int cpuId, LAD_DspStatus *statusInfo)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_releaseDsp</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga30ecbd942631db0ae030c78ba23387d9</anchor>
      <arglist>(LAD_ClientHandle handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_startupDsp</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga48bcbafcd3534ad79b31f09c8e99df1f</anchor>
      <arglist>(LAD_ClientHandle handle, Int cpuId, String linkConfigName, String imageName)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Memory.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/osal/</path>
    <filename>_memory_8h</filename>
    <class kind="struct">Memory_AllocParams</class>
    <member kind="define">
      <type>#define</type>
      <name>Memory_DEFAULTALIGNMENT</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gad3f3ab6aee96704cc82d79d8a3bb08a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_GTNAME</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga32a55c886c1233d7d3c865f57a5d8af7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_CACHED</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gaea7736ca0f8d012d8d0813a4e2871c64</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_NONCACHED</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga69466f2d58c621b9b1a8801d0de41b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_CACHEDMASK</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga0652dc1abbd60b09a391adb9f8e0ae32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Memory_type</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gac2a14a66c71e5108d4b029a2e0d940c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_MALLOC</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9af1d579534634486f6806cba8f5533279</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_SEG</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a1138288e1138d0608c8c525af37b6fec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_CONTIGPOOL</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a3b7e6ba0d9c2794302f897e423a5ed50</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_CONTIGHEAP</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a69776699cf99579da5bd02c9ff7e0031</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_alloc</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gad526de48c332226c46d312a512566a09</anchor>
      <arglist>(UInt size, Memory_AllocParams *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheInv</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gaf371d3bc92479fb36123670b223211ff</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheWb</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga5bf0f4cf9af5933dd7f9d2e486813ae4</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheWbInv</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga8ae58d5c6b83c607b925d41edd80f0b5</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_contigAlloc</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gadcc65a14970757fbb5bc4ff4e9730701</anchor>
      <arglist>(UInt size, UInt align)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>Memory_contigFree</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gae8e4e295e8faf95b92cc0886aa14c978</anchor>
      <arglist>(Ptr addr, UInt size)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>Memory_free</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga6f97024ed8b8da994a729ab87cc26c54</anchor>
      <arglist>(Ptr addr, UInt size, Memory_AllocParams *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_dumpKnownContigBufsList</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gae2b6a9cc903ee184803d78581cd815ec</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>UInt32</type>
      <name>Memory_getBufferPhysicalAddress</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab8ec2b9417f2e0d7b2a6e82849809914</anchor>
      <arglist>(Ptr virtualAddress, Int sizeInBytes, Bool *isContiguous)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Memory_getHeapId</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga261148d59a10332670f91cf5c7462fc0</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Memory_getNumHeaps</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga505cbdf622b39af1ce1816ef46f3afa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_getBufferVirtualAddress</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga9bd3cbcc7d8eceee82736f85c88b31d9</anchor>
      <arglist>(UInt32 physicalAddress, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_registerContigBuf</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab52db9600a898de8c2be8c026bb1f64a</anchor>
      <arglist>(UInt32 virtualAddress, UInt32 sizeInBytes, UInt32 physicalAddress)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_unregisterContigBuf</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga41460efdf79c34895257b9026acfcae8</anchor>
      <arglist>(UInt32 virtualAddress, UInt32 sizeInBytes)</arglist>
    </member>
    <member kind="variable">
      <type>Memory_AllocParams</type>
      <name>Memory_DEFAULTPARAMS</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab8c4500be062bef1624f2e073d23a838</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Server.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/</path>
    <filename>_server_8h</filename>
    <class kind="struct">Server_AlgInfo</class>
    <class kind="struct">Server_MemStat</class>
    <member kind="define">
      <type>#define</type>
      <name>Server_GTNAME</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab264678f3ca17eb9c2ffacacd0b77bb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Server_MAXSEGNAMELENGTH</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga305799c99b0eba1a69a5f37a0889346c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct Server_Obj *</type>
      <name>Server_Handle</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab249b418561d6d673a7412bd745408b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Server_Status</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gafb6db0d25514e36fd10b4336c8388ac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EOK</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0a97a8654b5c34c79f886d8aac27e8af0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOSERVER</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0afc59e30b03545a05cf9515e267454b32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOMEM</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ae6efeda9864aae45b0b27dbf0ab85c7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ERUNTIME</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0aa2cb90e4b726b9e5413f0bc8fea3bc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EINVAL</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ad9d0d3e0a9e25a126984423fdc8c05de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EWRONGSTATE</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0abb2d405c1d048bc9adc18b466711f067</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EINUSE</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ad3cd4be539595dcbe3b6ff22b055cdb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOTFOUND</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0a908ab6d9de61932d2d18e92ca930d88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EFAIL</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ab412a9ccade194d093661fab07fdcaa9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_connectTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga8c962a2b8c6c77d094f04a95867f6a34</anchor>
      <arglist>(Server_Handle server, Int *token)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_disconnectTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gac819d08852a05ce7e0b27b504717d2a7</anchor>
      <arglist>(Server_Handle server, Int token)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_fwriteTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gabf3d25f7f9043e7b1b9361fa30945c32</anchor>
      <arglist>(Server_Handle server, String prefix, FILE *out)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_getAlgInfo</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga4a452bdc479e8c0032638994589fc335</anchor>
      <arglist>(Server_Handle server, Int algNum, Server_AlgInfo *algInfo)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_getCpuLoad</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga286132d42e203cee6ffcd90aa350f0f8</anchor>
      <arglist>(Server_Handle server)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getMemStat</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga5ea4f6bfe49a820c18c41be08a5633ed</anchor>
      <arglist>(Server_Handle server, Int segNum, Server_MemStat *memStat)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getNumAlgs</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga1f8e0693b89cc1b2bc17be1ebd334216</anchor>
      <arglist>(Server_Handle server, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getNumMemSegs</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga29b243a3787ef9a481b7c42fc9392170</anchor>
      <arglist>(Server_Handle server, Int *numSegs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_redefineHeap</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga243526c5b7f2c05a42e794d41aef43f6</anchor>
      <arglist>(Server_Handle server, String name, Uint32 base, Uint32 size)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_restoreHeap</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab655c3a9370796a8f5bf8b99ee3974ee</anchor>
      <arglist>(Server_Handle server, String name)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_setTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gafa9cb503170965cf48160304d2b7c998</anchor>
      <arglist>(Server_Handle server, String mask)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sphdec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech/</path>
    <filename>sphdec_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="isphdec_8h" name="isphdec.h" local="no" imported="no">ti/xdais/dm/isphdec.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_EOK</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga92a3df918ba687b8f146036550ba5e60</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_EFAIL</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaf6367169b44ba184320d80745278d238</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_ERUNTIME</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaee67760059368856c531da207d076882</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_ETIMEOUT</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga7b7a56b232d6dbb02dc27aa306e28a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_FOREVER</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga2437e21028197990fb0c41d93d5b193b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_Status</type>
      <name>SPHDEC_Status</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga709a20a3cee84e1f8a5fb19075dba667</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHDEC_Handle</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga124f2ec0a80d2f16632370ffcbac67dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Params</type>
      <name>SPHDEC_Params</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaacff1229f5459ed1939251296cdb2633</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_InArgs</type>
      <name>SPHDEC_InArgs</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga63f28c45e727a836c94dfaec2c58bddc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_OutArgs</type>
      <name>SPHDEC_OutArgs</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga434544c79ca6cbd2496efa9d3efbe5ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_Cmd</type>
      <name>SPHDEC_Cmd</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga47cc6ecdf3b5ca74de1aadc31df27824</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_DynamicParams</type>
      <name>SPHDEC_DynamicParams</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga4e4aac5fde7c50998c26d24640b1c88d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SPHDEC_Handle</type>
      <name>SPHDEC_create</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga232c0776f4982c2201dfcb6757c0ffcd</anchor>
      <arglist>(Engine_Handle e, String name, SPHDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC_process</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga004f2e4c06475e1be6cfe5116de80027</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC_control</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gae5f46950b9a073d239a65b1f1384f358</anchor>
      <arglist>(SPHDEC_Handle handle, SPHDEC_Cmd id, SPHDEC_DynamicParams *params, SPHDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHDEC_delete</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gad5ea3449c6b526c2e28abe0e3d5acc3b</anchor>
      <arglist>(SPHDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC_processAsync</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gafa5ffa6904cf0b4b39568bd9759f4319</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC_processWait</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga577b44385b51c5096cd83fce8a7da2ba</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sphdec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech1/</path>
    <filename>sphdec1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="isphdec1_8h" name="isphdec1.h" local="no" imported="no">ti/xdais/dm/isphdec1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga5232ca694305259bb78819295f4dd759</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga433c4f9b5a8936915dfd0e3e1fbd028e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gafca3e9fd1bb4445bf78a54caa0096f3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gae61ef4c25010e9ed5889cc094a8ec1dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga85c427d8ec22820d6c4861fba4017954</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gae1ddcc35852dea0604c20c162e7518d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Params</type>
      <name>SPHDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga169fd7e3c58f327f6863d0ab0acee022</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_InArgs</type>
      <name>SPHDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf4691a7729e59c1bf020058e52761dc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_OutArgs</type>
      <name>SPHDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga55457f5b5dd1dbbd58136a3e8f0b8359</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Cmd</type>
      <name>SPHDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf6092fa1e6520963aac6677a9ef87f93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_DynamicParams</type>
      <name>SPHDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gacfb355f557a3fb8d02942d31b3c3631e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Status</type>
      <name>SPHDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga8e11c98ecdcb71083f14e20e3869d814</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gac8fe63b882294d4382f96e016a2fae74</anchor>
      <arglist>(SPHDEC1_Handle handle, SPHDEC1_Cmd id, SPHDEC1_DynamicParams *params, SPHDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>SPHDEC1_Handle</type>
      <name>SPHDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gabaaa5d041890db5856f581f7f14647b4</anchor>
      <arglist>(Engine_Handle e, String name, SPHDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaa3e46e8005792857153a2c7b24060301</anchor>
      <arglist>(SPHDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf412f1ac7e1916740b152651dae3c470</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga5e7eea24460f6d509d73b83eb1d0ff10</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga61dff9f5240d85fd6bd83ada4077ecd9</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sphenc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech/</path>
    <filename>sphenc_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="isphenc_8h" name="isphenc.h" local="no" imported="no">ti/xdais/dm/isphenc.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_EOK</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gad3f08f36137b28184206e0d556682382</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_EFAIL</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga8d14cdd1fd63c45e7beba62c464d7ead</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_ERUNTIME</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaba65f74077e9f5fabae6290f7daffc08</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_ETIMEOUT</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga8f46879ca0532bef39f747a0db90811c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_FOREVER</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gabdf81b5119e04965497bb3bc03a74d85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_Status</type>
      <name>SPHENC_Status</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaecd0677714912ab15eef0caea71fe740</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHENC_Handle</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf23679c72ae5ebdff50a41a303986c6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Params</type>
      <name>SPHENC_Params</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga2842b2174222faddcd192b21d3a8bbb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_InArgs</type>
      <name>SPHENC_InArgs</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga14cfec1b3a4ddd9ea05c948c7ab8a038</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_OutArgs</type>
      <name>SPHENC_OutArgs</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga4f72f1ded7ea0ff2436cb877348b621c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_Cmd</type>
      <name>SPHENC_Cmd</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga36c38dabf0e76a4997bea84c69f203a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_DynamicParams</type>
      <name>SPHENC_DynamicParams</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga84d4de5a24fd34088f2a89cee9740aae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SPHENC_Handle</type>
      <name>SPHENC_create</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gacbd1973199095f0ed887f1046eeff06b</anchor>
      <arglist>(Engine_Handle e, String name, SPHENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC_process</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf6814914e4bc450d2caa945391fe25ca</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHENC_InArgs *inArgs, SPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC_control</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga943e47b8ad0679f67a735c3179231e1a</anchor>
      <arglist>(SPHENC_Handle handle, SPHENC_Cmd id, SPHENC_DynamicParams *params, SPHENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHENC_delete</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gab01da27d7c58ef44be061fcbad6ae9b4</anchor>
      <arglist>(SPHENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC_processAsync</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gae7ff164fe01fd37dbd74a63c0660279b</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC_processWait</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga64c4f46e8e591762837a6421d44f6e62</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>sphenc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech1/</path>
    <filename>sphenc1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="isphenc1_8h" name="isphenc1.h" local="no" imported="no">ti/xdais/dm/isphenc1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga420b4ae18c77a3edc291a526215f8f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gab106e36e90336b0d89b07fc52c399b2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e9fdde5fb595bb033b8316b6074a96b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaecddcea3a2fec9db91b1ce1f1a14938a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga056c1db84c81ddcf329fa12389c71bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaeaae5baa057d761fdf0aaa2c1a90371a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Params</type>
      <name>SPHENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga94e8eddf1c310cc688a4acc5a23a55f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_InArgs</type>
      <name>SPHENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga1b8446b40a30318efd4b38a4f9cc1a2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_OutArgs</type>
      <name>SPHENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga37ba382f11470bbf0f418637310e7f7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_Cmd</type>
      <name>SPHENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaaacf82ccebcf2c82cf9080f33a5f2c46</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_Status</type>
      <name>SPHENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gac08769863d854dd6e2b3583d11a98af2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_DynamicParams</type>
      <name>SPHENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga1cf47ecb369d8aa3938fcc5036e5dfc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC1_control</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga9ef17b57fad768eee41970b68404e815</anchor>
      <arglist>(SPHENC1_Handle handle, SPHENC1_Cmd id, SPHENC1_DynamicParams *params, SPHENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>SPHENC1_Handle</type>
      <name>SPHENC1_create</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gabbaedd6e1b2a7e50c28eaf1d5b8ea076</anchor>
      <arglist>(Engine_Handle e, String name, SPHENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga42f0d42d062692e9749ba088111d7471</anchor>
      <arglist>(SPHENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC1_process</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaea7cf777f9a3913d41dc2739080841b8</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa5d8d68da3015bd180e68d0df90c7ec0</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga6b87cb1e8fed78dac4f6f3fb2c147d04</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TraceUtil.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/utils/trace/</path>
    <filename>_trace_util_8h</filename>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>TRACEUTIL_SUCCESS</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga36e6d1770c3a6567a142d3d0d9926d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACEUTIL_FAILURE</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga832483a3bbe3e98452265e8137f24a9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>TraceUtil_start</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga0c1afd5c5805fd3c62dc81102f86ebd5</anchor>
      <arglist>(String engineName)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>TraceUtil_stop</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>gae0fac5c1e0c29072fbdb81d944836bc0</anchor>
      <arglist>(Void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>universal.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/universal/</path>
    <filename>universal_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="iuniversal_8h" name="iuniversal.h" local="no" imported="no">ti/xdais/dm/iuniversal.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EOK</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gade20f2e69755596e8ba0c5492655ca8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga84a0b3a478663ef705e5892e98ec3841</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga2306b8d762ca96d1ffeaf28832dd64cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga56ab6f1bc8ebd19c9493ba51d106427f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga91688034ef01f08d844489c691a560fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>UNIVERSAL_Handle</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaf94abf3f8d7de2270695a31426498faa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Params</type>
      <name>UNIVERSAL_Params</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga867a8bdef066f152335d31a70e00337a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_InArgs</type>
      <name>UNIVERSAL_InArgs</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa6de5f43e559d284735ef9dfcc437cc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_OutArgs</type>
      <name>UNIVERSAL_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gab00531077258820bd52e301929d7defc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_Cmd</type>
      <name>UNIVERSAL_Cmd</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gabfedfad116072edc4a8b7bb40cc9dfbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_Status</type>
      <name>UNIVERSAL_Status</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga7e6fc87fed2880856afd08057372ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_DynamicParams</type>
      <name>UNIVERSAL_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga81291e811b04126a73c48cf94869c533</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>UNIVERSAL_control</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa5ead906fb8d7f70895bd1618b7b5bca</anchor>
      <arglist>(UNIVERSAL_Handle handle, UNIVERSAL_Cmd id, UNIVERSAL_DynamicParams *params, UNIVERSAL_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>UNIVERSAL_Handle</type>
      <name>UNIVERSAL_create</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaab5b0e7fa752fb4721dcfd72c77e4aae</anchor>
      <arglist>(Engine_Handle e, String name, UNIVERSAL_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>UNIVERSAL_delete</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga3f7b0d2a2d83ef78249d1896eec66d8f</anchor>
      <arglist>(UNIVERSAL_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>UNIVERSAL_process</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga63642cb1a9c0e2a9970a5cf8b78ee727</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, UNIVERSAL_InArgs *inArgs, UNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>UNIVERSAL_processAsync</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga352bfc67746de2ef1c210fff6d55ca0a</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>UNIVERSAL_processWait</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga20dc67d51e8af763135d52fa601a5b00</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>vidanalytics.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/vidanalytics/</path>
    <filename>vidanalytics_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividanalytics_8h" name="ividanalytics.h" local="no" imported="no">ti/xdais/dm/ividanalytics.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EOK</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga0e822caf655ba6614fb29af0ea2ab954</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5e22f8669f1f8b477065fa1b5a596ab6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga95bfaa4802d03a8522ed71de50c396c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3e8ab8c4c1dbc7612461bcd9998d7709</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gafdc3d27c7684d46971f3c9e6c6fb9d03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDANALYTICS_Handle</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga7b1cfa512e1fdbaf0dec0504f9030dfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Params</type>
      <name>VIDANALYTICS_Params</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade82de22bf14e7c26228de02a97c8505</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_InArgs</type>
      <name>VIDANALYTICS_InArgs</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga66d090369dd7cd22546bc58f16a597b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_OutArgs</type>
      <name>VIDANALYTICS_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac540b9a8699431477786da498b90943d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_Cmd</type>
      <name>VIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaaa6db913ea6f620f04341a7cc163fd1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_Status</type>
      <name>VIDANALYTICS_Status</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa36b9ad7b1697fa8297383ef25c16f57</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_DynamicParams</type>
      <name>VIDANALYTICS_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga732f41d71282aa4ca090eb576f53308c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDANALYTICS_control</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga7647b22d5c00bb0eef791f8835b3f3d8</anchor>
      <arglist>(VIDANALYTICS_Handle handle, VIDANALYTICS_Cmd id, VIDANALYTICS_DynamicParams *params, VIDANALYTICS_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDANALYTICS_Handle</type>
      <name>VIDANALYTICS_create</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga475a5abb26a90250ff1e08b7dbbbbf63</anchor>
      <arglist>(Engine_Handle e, String name, VIDANALYTICS_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDANALYTICS_delete</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga846c8e8530f77bf98350357080990a78</anchor>
      <arglist>(VIDANALYTICS_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDANALYTICS_process</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga98b6938cbd2df4278724f153801ac304</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, VIDANALYTICS_InArgs *inArgs, VIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDANALYTICS_processAsync</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga992c1e5deadb65ddcd8c9dfb50e97678</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDANALYTICS_processWait</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga738e654701f883c9a2512a009297ad1d</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>viddec.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video/</path>
    <filename>viddec_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividdec_8h" name="ividdec.h" local="no" imported="no">ti/xdais/dm/ividdec.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IVIDDEC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_EOK</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gabe8baab72eab6424a41a0a334494a612</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_EFAIL</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaa249b3a8fd01220a42f36b7707241a09</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_ERUNTIME</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga146bda97c8799172061993fcefc8fe13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_ETIMEOUT</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7e936b48259312164afce8fec9a6ce8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_FOREVER</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga06f0c028245349a1a7d9b1e90f8cbda8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_Status</type>
      <name>VIDDEC_Status</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf616c0e56d16935941dab2be391de913</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC_Handle</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga92af2feff2dd294d434283085ddead93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Params</type>
      <name>VIDDEC_Params</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaabd72bd755a04c88491205a3f9fe839c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_InArgs</type>
      <name>VIDDEC_InArgs</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga55e28d443fb4ee87d6bc5c9b4d6e063e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_OutArgs</type>
      <name>VIDDEC_OutArgs</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f35489e308e32dadf4a37b102eb9541</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_Cmd</type>
      <name>VIDDEC_Cmd</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga4c04ae2e12da9b8cf009476ef20e154c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_DynamicParams</type>
      <name>VIDDEC_DynamicParams</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf9afbae3ad253f919a948aafd30ac07d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC_Handle</type>
      <name>VIDDEC_create</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga8ed0216fe02a3ba35a0672fd7df00079</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC_process</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaab4faa31ebf26cf9c182d48417ea205c</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC_control</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3a8e01918dff1f556a18968ce96611c8</anchor>
      <arglist>(VIDDEC_Handle handle, VIDDEC_Cmd id, VIDDEC_DynamicParams *params, VIDDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC_delete</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gadf312f577bb4f0040eceede27de93b37</anchor>
      <arglist>(VIDDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC_processAsync</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga8f6138c30e0856574e0829fe1807bd59</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC_processWait</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gac8dcb55012c5e2360f025489b3457fb1</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>viddec1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video1/</path>
    <filename>viddec1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividdec1_8h" name="ividdec1.h" local="no" imported="no">ti/xdais/dm/ividdec1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IVIDDEC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gabea208cf8275b6267f338f3e58bd2eda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae412e487e8adee75b0b57d17740af43b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga9357b6663fdd9da55639389904a9c0f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga772eaf3172b528c7c6aa002a400cb21c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae1f23780dcc21fc13b2e5c7e53cb1455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_Status</type>
      <name>VIDDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga74bbcba5eaa9e453394132ca532162ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga1f1ddc163e5211b25047e7d848025620</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Params</type>
      <name>VIDDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga872f6fb297fe7326cbceb54396e8fce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_InArgs</type>
      <name>VIDDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga74ac24e03859ca89e1824e73e455a3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_OutArgs</type>
      <name>VIDDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga01cdae55d171241b1f214045b67ebc92</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_Cmd</type>
      <name>VIDDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaa483cca0045f226d99458f15a0fb6cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_DynamicParams</type>
      <name>VIDDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga10255d56ff2813f7c337edc25c11ee36</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC1_Handle</type>
      <name>VIDDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga96bf80485afe49b889761b17fbf9eef5</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga30436231ebf7f58455177dcd1fbabe12</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga7b8aeb30459218bdff63d38eaac5b2ec</anchor>
      <arglist>(VIDDEC1_Handle handle, VIDDEC1_Cmd id, VIDDEC1_DynamicParams *params, VIDDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga9928301c0880243d149cbc85871f216d</anchor>
      <arglist>(VIDDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga1ed176130043de491e631255700622a5</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gabf7ba6ea9536c583979edb1082baf0db</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>split/viddec2.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video2/split/</path>
    <filename>split_2viddec2_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="split_2ividdec2_8h" name="split/ividdec2.h" local="no" imported="no">ti/xdais/dm/split/ividdec2.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <includes id="viddec2_8h" name="viddec2.h" local="no" imported="no">ti/sdo/ce/video2/viddec2.h</includes>
    <class kind="struct">IVIDDEC2BACK_CodecClassConfig</class>
    <member kind="typedef">
      <type>IVIDDEC2FRONT_Status</type>
      <name>VIDDEC2FRONT_Status</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga891a3eae7577a2cfe055450915c9d91a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga6f2df412d30edb0a9eef16a5c1e8a811</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac2b371eda3c2797d4baaa5562e06be26</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2FRONT_OutArgs</type>
      <name>VIDDEC2FRONT_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9269db4573b24702bbc06d98cb8f9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2BACK_Handle</type>
      <name>VIDDEC2BACK_create</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga20a1d1dc28b380ee28abbe218089540e</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2BACK_process</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaf43b4174649994910eb79da042d8323c</anchor>
      <arglist>(VIDDEC2BACK_Handle handle, XDM_Context *context, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2BACK_control</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7cfc70c5b7dbe2682a6bcae620a10710</anchor>
      <arglist>(VIDDEC2BACK_Handle handle, XDM_Context *context, VIDDEC2_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2BACK_delete</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga872721952f0336f9163b5fba807e12f3</anchor>
      <arglist>(VIDDEC2BACK_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2FRONT_Handle</type>
      <name>VIDDEC2FRONT_create</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga1826ac5b4bcaf171b160252ed31524c6</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2FRONT_process</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa394094a6be5bd28a5f72291a95d3f1b</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle, VIDDEC2_InArgs *inArgs, XDM_Context *context, VIDDEC2FRONT_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2FRONT_control</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga457bfc26428e0dc7196b8ed022ad1438</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle, VIDDEC2_Cmd id, VIDDEC2_DynamicParams *params, XDM_Context *context, VIDDEC2FRONT_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2FRONT_delete</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga48d6c3eaa755fb821d466879359c8cc2</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>viddec2.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video2/</path>
    <filename>viddec2_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividdec2_8h" name="ividdec2.h" local="no" imported="no">ti/xdais/dm/ividdec2.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IVIDDEC2_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EOK</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga17a280c6bc345a31e94a2ccfbad75e30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gabb22d106ff08094e22232b73b2c13151</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga6684057aee13ca029c22820491c816c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gadde8d402919cb93efeaad88207db5c01</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8db99cb190a3ee911cbbf25b22ac0751</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga825bedfe8430826abe48cf19cde5bcc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Params</type>
      <name>VIDDEC2_Params</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga574bccbb2b8cdd6cef48c4509cee4a04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_InArgs</type>
      <name>VIDDEC2_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga69f197d86e2e9db761ad6ae75569771e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_OutArgs</type>
      <name>VIDDEC2_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga61407f29da10c8e036ba3d847d2d4ec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Cmd</type>
      <name>VIDDEC2_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga881b58af927563dfc3e920aaab508e8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_DynamicParams</type>
      <name>VIDDEC2_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaf527166a656bd4278329ae28ddf96729</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Status</type>
      <name>VIDDEC2_Status</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga82b958e99f98898c9a769f501e112979</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2_control</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac56066dfb51357ff6a7e85c39c6923d3</anchor>
      <arglist>(VIDDEC2_Handle handle, VIDDEC2_Cmd id, VIDDEC2_DynamicParams *params, VIDDEC2_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2_Handle</type>
      <name>VIDDEC2_create</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga18eacdfbf4cedbfa125d6e3aabbf93be</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2_delete</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7a16583250a5169335bd4ea6a39f5751</anchor>
      <arglist>(VIDDEC2_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2_process</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa9fdbcf0841f7e8283764b3b75d61313</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC2_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac8f023338811207859cb38a6ac46e5f6</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC2_processWait</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gad3aef2ba0e5e3682467a1caea51a7483</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>videnc.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video/</path>
    <filename>videnc_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividenc_8h" name="ividenc.h" local="no" imported="no">ti/xdais/dm/ividenc.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <class kind="struct">IVIDENC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_EOK</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga8776fd0a4ddd63edd36f3979dfddb9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_EFAIL</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gaa6c3de08b2a584976be0ffde2c4b81b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_ERUNTIME</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gac411d1a2c3e5c67a5718287d317a5483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_ETIMEOUT</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga6eaed37ed3338e8de39c6a258362dc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_FOREVER</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga4807e4e1fbf632d1c9e22772d15c8b74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_Status</type>
      <name>VIDENC_Status</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga15fc4a0dd5b06f14b8509091a1107283</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDENC_Handle</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga60925466f910025443b791cd7894cc56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Params</type>
      <name>VIDENC_Params</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga376be7b4739d843736f3056b46cfb35c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_InArgs</type>
      <name>VIDENC_InArgs</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga21aae5070ed29e590579ac1c84f56b20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_OutArgs</type>
      <name>VIDENC_OutArgs</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga50ec5c9f9cdc4ba3db8f8872ed2ef523</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_Cmd</type>
      <name>VIDENC_Cmd</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga926b28b5c17d2e610c45aa71d0628199</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_DynamicParams</type>
      <name>VIDENC_DynamicParams</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gae88a985907e854439eae82add1c74aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDENC_Handle</type>
      <name>VIDENC_create</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga86a8acd4d73fa48db484000ff2960485</anchor>
      <arglist>(Engine_Handle e, String name, VIDENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC_process</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga9dc7650ae11474f7b80209ec6268885d</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDENC_InArgs *inArgs, VIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC_control</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga9e61bdaa46802daa9847a46a7c04df4e</anchor>
      <arglist>(VIDENC_Handle handle, VIDENC_Cmd id, VIDENC_DynamicParams *params, VIDENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDENC_delete</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga79a7f95f66d5dac756f8c13db7bc74ff</anchor>
      <arglist>(VIDENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC_processAsync</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga5c572b93e4213eb2419af7ee5fd51eda</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC_processWait</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga59e66a5eab3c01669bf5067310e44b28</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>videnc1.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video1/</path>
    <filename>videnc1_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividenc1_8h" name="ividenc1.h" local="no" imported="no">ti/xdais/dm/ividenc1.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf27bfd83fb1e65f85f6985a1573bae40</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga42effe0110f0c61408fe59f4b1ed7555</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gac6ba8504c98c6dd6a2475d2f3e893547</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gad5790cadb1681ae5989a14da65068519</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga5a8494b6501ae82147533f482ad31869</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_Status</type>
      <name>VIDENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8977b714f595bca81f381cb44f079b0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga422c0ee1b56306b13c598d0d9718db50</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Params</type>
      <name>VIDENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga3b71b156c370cb7d2c260421c1a60d76</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_InArgs</type>
      <name>VIDENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gad088c2553eddd215647f4670e7c6f24d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_OutArgs</type>
      <name>VIDENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga9939b7fa369bd00d82e727fb0bc35aad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_Cmd</type>
      <name>VIDENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2cd4de792e4191e0fad7adccbb2e337c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_DynamicParams</type>
      <name>VIDENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga604ea63d97916c49027e7c172964e00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDENC1_Handle</type>
      <name>VIDENC1_create</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga5100bd55908105eb918430a13b4c964d</anchor>
      <arglist>(Engine_Handle e, String name, VIDENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC1_process</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga84cc9c14cb3fb8d5104864e0bb91c430</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, VIDENC1_InArgs *inArgs, VIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC1_control</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf24ed59a2cf8589af04868d2c3a3ea09</anchor>
      <arglist>(VIDENC1_Handle handle, VIDENC1_Cmd id, VIDENC1_DynamicParams *params, VIDENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga203fcb7c17c37398f03dd6df2b08ae05</anchor>
      <arglist>(VIDENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga4d59054512de34e9a765874db7ca0587</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gabeb4b67c5c85568d00bbbf982e69a315</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>vidtranscode.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/vidtranscode/</path>
    <filename>vidtranscode_8h</filename>
    <includes id="xdm_8h" name="xdm.h" local="no" imported="no">ti/xdais/dm/xdm.h</includes>
    <includes id="ividtranscode_8h" name="ividtranscode.h" local="no" imported="no">ti/xdais/dm/ividtranscode.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <includes id="visa_8h" name="visa.h" local="no" imported="no">ti/sdo/ce/visa.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga4947ac42f9f0f2f7c1c9a87a210c739b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gac61f5cae4837ad8b98b01184d777d812</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae522ab0ff96ec987ac91267a241fbc6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga805de75c31022068be40a35d71db5be0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaa00159f19b62efc8b3f587c0a9685026</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaaf087646fa33289c25338a3732a113cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Params</type>
      <name>VIDTRANSCODE_Params</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga3a8256b227d1b242ce8d440bb4f77e44</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_InArgs</type>
      <name>VIDTRANSCODE_InArgs</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae6d29cb086517d71502a98e57813d120</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_OutArgs</type>
      <name>VIDTRANSCODE_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae1c69202d86064a5921ef4278b694440</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_Cmd</type>
      <name>VIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga51fc2c5f7247b0568219f4d59b55dd5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_Status</type>
      <name>VIDTRANSCODE_Status</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9fc37e582bba0df08dc414a4deedf225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_DynamicParams</type>
      <name>VIDTRANSCODE_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga14984cc5d63cfac48889c0990a8d3fc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDTRANSCODE_control</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga903722dd7468db37879e5a2552ed8464</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, VIDTRANSCODE_Cmd id, VIDTRANSCODE_DynamicParams *params, VIDTRANSCODE_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDTRANSCODE_Handle</type>
      <name>VIDTRANSCODE_create</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9d960312911326bcfc63986ffbfb9a98</anchor>
      <arglist>(Engine_Handle e, String name, VIDTRANSCODE_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDTRANSCODE_delete</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga7054b57f8dcc78871d26dc8f2802f7fe</anchor>
      <arglist>(VIDTRANSCODE_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDTRANSCODE_process</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9e1e02c13d93a607fa824c84813f37c3</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDTRANSCODE_InArgs *inArgs, VIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDTRANSCODE_processAsync</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaa1bc43c4f87a40841583ad98eb9ff182</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDTRANSCODE_processWait</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga640c33a61a07c41ea4deff528b4f3968</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>visa.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/</path>
    <filename>visa_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="_engine_8h" name="Engine.h" local="no" imported="no">ti/sdo/ce/Engine.h</includes>
    <class kind="struct">VISA_MsgHeader</class>
    <member kind="define">
      <type>#define</type>
      <name>VISA_EOK</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga2edbcef572bbd8d30c6bb349db86fe5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_ERUNTIME</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaad5846943a2f5bc0fab9ce0cfb0e11aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_EFAIL</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaa1444d9197068455a077da8d42462b16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga982385711ed018e821510af2ae34decf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_FOREVER</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga4357bfb7aae9bdb6f49a67df470249a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int</type>
      <name>VISA_Status</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaaf6296a78da6640be7ec774731d9b100</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct VISA_Obj *</type>
      <name>VISA_Handle</name>
      <anchorfile>visa_8h.html</anchorfile>
      <anchor>ad2d626392f96026cd951ba452146406b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_MsgHeader *</type>
      <name>VISA_Msg</name>
      <anchorfile>visa_8h.html</anchorfile>
      <anchor>a4fa23046523fbcf5d8484b8ea8b0c8e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VISA_Msg</type>
      <name>VISA_allocMsg</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gabf5c5af35ea69f1ef725b5bfd6faa912</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_call</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga1ef4ab81afea6e041c7d36f88cc180a8</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_callAsync</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gad92dedea2968a5ef4aa8b12675c0af44</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_wait</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga6087effc1133a0ad99ae68c3cc1233cf</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg, UInt timeout)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_freeMsg</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga36209656e4a94e17c8edded097ab95cc</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg msg)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_getAlgMemRecs</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga2c45fde612a6f225bb6498120d7d87e1</anchor>
      <arglist>(VISA_Handle visa, IALG_MemRec *memTab, Int size, Int *numRecs)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_getAlgNumRecs</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gac6783c6ff2b4f8338f1c82249bdc5fe3</anchor>
      <arglist>(VISA_Handle visa, Int *numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_getContext</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gaf267d181beb7da616c423a934ea9a92c</anchor>
      <arglist>(VISA_Handle visa, UInt32 *pContext)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getCodecClassConfig</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gabf9abcbb0df0613151195aba068a30f8</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>UInt</type>
      <name>VISA_getMaxMsgSize</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga17cce3a55dc66766af54966406dcf0e0</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_setContext</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga81d34e425ad23de06e05e7996dbfde94</anchor>
      <arglist>(VISA_Handle visa, UInt32 context)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>VISA_isLocal</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gad9a95e8263867eea049235d2ffc61668</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Handle</type>
      <name>VISA_create</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga0763f9de306c1e8c3ed68ef849234b94</anchor>
      <arglist>(Engine_Handle engine, String name, IALG_Params *params, size_t msgSize, String type)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_delete</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga3bec94bcc2149b76ec4f51bd968744e5</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Handle</type>
      <name>VISA_create2</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gaca27816a9a296b172f819f5a074fb812</anchor>
      <arglist>(Engine_Handle engine, String name, IALG_Params *params, Int paramsSize, size_t msgSize, String type)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_enter</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga8dbcaeadf2a560877db77c61cc67342f</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_exit</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga2ea2abaca0018497421126bdf63136be</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getAlgHandle</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gae8bf0905dd129158701623b858e83e92</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getAlgorithmHandle</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gabe11eada20b930e4eb019c3ca75a1e36</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Fxns *</type>
      <name>VISA_getAlgFxns</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga5c8a043fd48d1c00f22d213e5062e614</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xdas.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/</path>
    <filename>xdas_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_TRUE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga0a1e9fe6b661ca6eafe982fe2b0787bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_FALSE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga5cd894ca3ba5c100f7f863dae8587293</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void</type>
      <name>XDAS_Void</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga125aad4180e7ca9a3ddaba59c9217513</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_Bool</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac8ce48f3d618a6f0a37b4e55f978b825</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int8</type>
      <name>XDAS_Int8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa0b0c4cc1bf0d8fa0d9b15de0e9204cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_UInt8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac9308edb855a360c27a47aaa6f3b39a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int16</type>
      <name>XDAS_Int16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga8189aa7a8636f505d6a35e5744ac6392</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint16</type>
      <name>XDAS_UInt16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa27605972947c862397ebee40c2ff917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int32</type>
      <name>XDAS_Int32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gae431579ed9eff9134de78ca00ddd5f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint32</type>
      <name>XDAS_UInt32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga615572fcd2279a6780dc1785d72ff421</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>xdm.h</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>xdm_8h</filename>
    <includes id="ialg_8h" name="ialg.h" local="no" imported="no">ti/xdais/ialg.h</includes>
    <includes id="xdas_8h" name="xdas.h" local="no" imported="no">ti/xdais/xdas.h</includes>
    <class kind="struct">XDM_BufDesc</class>
    <class kind="struct">XDM_SingleBufDesc</class>
    <class kind="struct">XDM1_SingleBufDesc</class>
    <class kind="struct">XDM1_BufDesc</class>
    <class kind="struct">XDM_AlgBufInfo</class>
    <class kind="struct">XDM_Date</class>
    <class kind="struct">XDM_Point</class>
    <class kind="struct">XDM_Rect</class>
    <class kind="struct">XDM_ContextInfo</class>
    <class kind="struct">XDM_Context</class>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EOK</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1cf6109227485a043be42d0761ed55b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac896f031d1997aae6f959aff6c6d8b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac502a6ae2494d2c4151e2a3be22c96e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa1a1d3d9c0c8807cbe465633d76580e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacb0db1cbd37d45e39368c0dff87d7cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3446a438727f673f58cacd76947536d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa0360329abe8080abb150c24255fa3a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaedd624063fce29cfed9193ad4d46765c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacaf2e719f6570fb074df83697f9665d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c3d846ed83c34a06fd6e8fcb49b4b2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaef2577b3a010843a01d85a6e2bbf5487</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMENUMBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6eae9fc7c3a5e8aa08d3d23d870b583</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMCMDBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga43093f03f01c2e4eed7f131795af84fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf46ec0675f5fae35aaf29392aebbe3d3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gae1b52e8b2c8c062dd460f8a9bc737b77</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacc71215dc73ce6f3184f78be7c49ac09</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4979bf4ca24fca5d9386896f9c319084</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga180c829e45389f064af38a3e58278baa</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7714cc631b009ef2c574218006af0ebb</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga24d74d9ea55947f6bf2bc90a532bc32c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab0d647a23e89f0a11fb47493746bc254</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad4b20720fe6a8d9eb46259206635c6ab</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6a007a552f8849694b6c785531c9413</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad5b5a780c1df72c1a99f28c1e32531be</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7cab971a59a1057febe113621ac68c1b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga89f38db60d38746c435f8d9f2398bef2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga22e33071e27e1f3d1624229986c79331</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_CONTEXT_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaed28c56a4d5a516897357c2fc647ac9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_AccessMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad852bdfa0303e77939811768b8e905ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905abadc6547990f2ba9c7a4bacdf3ad4f405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905ababd16ad36f147cf0e691a13590314a06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_CmdId</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4d2482d53629e138b96af2e3fe702477</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETSTATUS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a901d6409e5496dbc7720d0e952fb1b15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETPARAMS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477ab358f49d17f79c00b1ba5c2c645eb025</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RESET</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a2bf3cef324828ab92cd6cedead4c725e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1b6cda1632a452aa55dbba763b53d746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FLUSH</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477acd0e4d7005b1df978b26f97bccf6df8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETBUFINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477aac803fc3c3144acc395e3b9b79025653</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETVERSION</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a6531ed0c0766017f6caa01207d3ad4c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETCONTEXTINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7aa270e718dce742ef06b8d67be98055</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ErrorBit</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga993de0b923e61c59a996fc2be4783131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARAMSCHANGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a13eb40f973b1bc18df8263030d4a1be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_APPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a143f0496fb2db7191d7ddbe9d9fb58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_INSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131aeb5f7b677fb1d35ce8c9e4af0e1c5c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3df4766dd604b28652b8830f051a7e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131afab843e2d029e916fc36e7550489dba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a7c4145225db773b55c02bcc61be59756</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3440c95956b613e002620a71c77a5980</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a8ebb569b30333486afaf576c366118e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DataFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga5b4416e5582cae4428a1f4695d6e5ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BYTE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5aa24eeba74896e53a4bb8874560e4f67d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a286615517f0d85bbad01a61ca1b8355b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a87cbb4b143f78faf0f5c67d45cd5a39a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a111d1dcf71c52bd2c9886373a5d98e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a3dac2b3e9961a294c89ffac5ceedb509</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a43e43097fd1b63ac44247df52fe88da4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a82ae547ec4f91e70c0dec56dd35c624d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncodingPreset</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7b522f4337b661bbf9fb649eb95b4e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca72b9373f4561db5fc6b0a2904b4a40e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cabef4cff45b90786a8583b027530bb927</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf553ad9672b1ee9a7b91d746980dc58a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caba3ac3c750ac0125c9f1aac6f8586b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DecMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga0e19341fdb7c698eb849896edaa33aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DECODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa8c540496685639e09e8c1ef895565595</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARSE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa20a585ea8dd3b153c5203499b54d862c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7e9132a2379c6ac0ee9c9e925b932461</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a5822b75801cd51f3a5f3478d59c8bee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GENERATE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a98969caa951cc0b210bacdd2a1932abc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ChromaFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab99980ebd17efe73aa5708b5f43107f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMA_NA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aef81026a1d1783d9628c19f5c8a78dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a891298e42c828a4c56b2d20d8be7cca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9457339c11ffa04dca5f900e82a2346d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422IBE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a638d86b7f38f9404348b38fa459bdee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9560c4d0b7a2ddb6aba01ca66e41e5ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a31ade59366a5116a6d74a4fe012021f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_411P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6c2c3aac53d2a8da477f487d788bcb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GRAY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a45edf9e2ce7ab4045dfcdde062b4e423</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a0491c6350cc8c9127610c2a6c31f3ee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420SP</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4acd45176e14ea9e5b53fc52ec88bddd9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ARGB8888</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a5979b38c73531a7bf71c12412232be5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB555</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aa1ae21243fd451d6a8f75bd274a77934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB565</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6b8863fc2937c932888f3df04ff1bcc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aaf1809f33e309f991f8c47b6af55399a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMAFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4af01b00784f3926f7accfd6f0a8360a7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>Disclaimer</name>
    <title></title>
    <filename>disclaimer</filename>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDDEC</name>
    <title>XDM IAUDDEC Audio Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_d_e_c.html</filename>
    <class kind="struct">IAUDDEC_Obj</class>
    <class kind="struct">IAUDDEC_Params</class>
    <class kind="struct">IAUDDEC_DynamicParams</class>
    <class kind="struct">IAUDDEC_InArgs</class>
    <class kind="struct">IAUDDEC_Status</class>
    <class kind="struct">IAUDDEC_OutArgs</class>
    <class kind="struct">IAUDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gae550832bf925622e32ea891f9a64f840</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0447e3d9eba91c950b0ca6533f090b4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9ba0561ce6c276ef9a4b9d6dc1b66aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>gacfdf5e7ab31ee37a9b168bbcf7d71309</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Obj *</type>
      <name>IAUDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga849224ef7d8add16e7152e3c2cef1cb0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c.html</anchorfile>
      <anchor>ga8a44a541760fefd4c41ea1d29c80d71e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDDEC1</name>
    <title>XDM IAUDDEC1 Audio Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</filename>
    <class kind="struct">IAUDDEC1_Obj</class>
    <class kind="struct">IAUDDEC1_Params</class>
    <class kind="struct">IAUDDEC1_DynamicParams</class>
    <class kind="struct">IAUDDEC1_InArgs</class>
    <class kind="struct">IAUDDEC1_Status</class>
    <class kind="struct">IAUDDEC1_OutArgs</class>
    <class kind="struct">IAUDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2875d67b3c5af6d7a16b373ec21cf567</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2ac49534acb4a9fef6c32355b9883664</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga690d6e129037630a13d1b80eb1e2480d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Obj *</type>
      <name>IAUDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga2287de2327bdc6e94ada6971506a2fe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4c0ee4ad90447b42d3a39dd6e81ca3c7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDENC</name>
    <title>XDM IAUDENC Audio Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_e_n_c.html</filename>
    <class kind="struct">IAUDENC_Obj</class>
    <class kind="struct">IAUDENC_Params</class>
    <class kind="struct">IAUDENC_DynamicParams</class>
    <class kind="struct">IAUDENC_InArgs</class>
    <class kind="struct">IAUDENC_Status</class>
    <class kind="struct">IAUDENC_OutArgs</class>
    <class kind="struct">IAUDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2c2cde30bd98faf8f6e88058e766c432</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>gac95ad430142a56f43f9f822372cd55fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga277eb1ae03f2becd10f2e62804e68876</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga8955b9b4eff0b4105d71a7e13e4b1292</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Obj *</type>
      <name>IAUDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga67b207a9e6d7ac649cf393bf9b89a758</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c.html</anchorfile>
      <anchor>ga875abe1167c5304cec0cb23421f3215a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDENC1</name>
    <title>XDM IAUDENC1 Audio Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</filename>
    <class kind="struct">IAUDENC1_Obj</class>
    <class kind="struct">IAUDENC1_Params</class>
    <class kind="struct">IAUDENC1_DynamicParams</class>
    <class kind="struct">IAUDENC1_InArgs</class>
    <class kind="struct">IAUDENC1_Status</class>
    <class kind="struct">IAUDENC1_OutArgs</class>
    <class kind="struct">IAUDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaca757d01864682f891f4e79e27612615</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3b351ca3f8350018b9411570be9a0e63</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IAUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gace019d488c6e5825adcf3950246b2ea5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Obj *</type>
      <name>IAUDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga674429c3839d2412844c94f288c88493</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IAUDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab08988284a4cb6779e196509c28705d0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IAUDIO</name>
    <title>XDM Audio Interface</title>
    <filename>group__ti__xdais__dm___i_a_u_d_i_o.html</filename>
    <member kind="enumeration">
      <name>IAUDIO_ChannelId</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga2f7957b5da562687498a612165664179</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_MONO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a5f4470f75c884f7e4b04ca5f14ad7acf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_STEREO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a99e682b79cf46c280e7bafb9470b8f2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_THREE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179aeabcf85e87c1c856a80b9824220aaaa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ZERO</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a9f5cb587cdcfb58952ecebce56532568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_FIVE_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a05f535ae3ec20c8f007b9139eda2be73</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_SEVEN_ONE</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga2f7957b5da562687498a612165664179a092297b5eee8fa4bf24b7bac35a5c8ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_ChannelMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga42c416b540264a57d8728b07d765b14d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_1_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da4a44a2c8361fe98d5a083c7a067933e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da8cf64356a7097cea1e401ab31d7f5f8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_11_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da97b04f3a5f55abc03ec813694b1236d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_0</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da66f93b5b1244b8c4386f7f2bfdd81783</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da1f7b4e0d6455df92a428c33848351b45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_1</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da77f0db8024cbb1df8d501f11b3b6ee11</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dacafa604d4031971085a63e74c6a1377a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_2</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dac912907baaca2ef193290fb54359d022</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_2_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da022f51b4b16ed20be3a67fba6247a54a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_3</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14dae2eaa060c3dc06e7126eb088f2639466</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_3_4</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga42c416b540264a57d8728b07d765b14da0de8b72246498dc39781fa6f8f88feb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_DualMonoMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga3d6a55ad8d567db30ddca14e0180b501</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a91fc7e77ba226b15008e2bcdc54e196b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LEFT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a33cf98bc81668fe9dc4eae0f5c41780b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_RIGHT</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a7ac285c92ea3048e5ed006af3d453b42</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_DUALMONO_LR_MIX</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga3d6a55ad8d567db30ddca14e0180b501a0358f0cc0ad00b1551e0f7387b112e3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_PcmFormat</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gac631266018b8f5df7df1e52f65c2757f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_BLOCK</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757faa072981204cf2b0d1cdddce4d9644154</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_INTERLEAVED</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ggac631266018b8f5df7df1e52f65c2757fa12f80fc0827105d6dc1df1dda485d161</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IAUDIO_EncMode</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>ga1d8af2cbae15bc609badbb328ab3a08c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_CBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08ca422efb88eb135a5212bfa6b3600c35a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IAUDIO_VBR</name>
      <anchorfile>group__ti__xdais__dm___i_a_u_d_i_o.html</anchorfile>
      <anchor>gga1d8af2cbae15bc609badbb328ab3a08caf311198449fe7e6c2e20f79d66b7a0e8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGDEC</name>
    <title>XDM IIMGDEC Image Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_d_e_c.html</filename>
    <class kind="struct">IIMGDEC_Obj</class>
    <class kind="struct">IIMGDEC_Params</class>
    <class kind="struct">IIMGDEC_DynamicParams</class>
    <class kind="struct">IIMGDEC_InArgs</class>
    <class kind="struct">IIMGDEC_Status</class>
    <class kind="struct">IIMGDEC_OutArgs</class>
    <class kind="struct">IIMGDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga399a3c00c3d9181c9b84a86549c76344</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4c2d7f1c15e1bfb70a61ae987979ad3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf11d65f2c57f70bfa994221f201fe483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gac0a3c1ac74db21cce563ac1af0dcdcf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Obj *</type>
      <name>IIMGDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>gaafcce966766ae1ec2ba860294450603c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c.html</anchorfile>
      <anchor>ga6d702c2802e8827926120bfeef5de0ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGDEC1</name>
    <title>XDM IIMGDEC1 Image Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</filename>
    <class kind="struct">IIMGDEC1_Obj</class>
    <class kind="struct">IIMGDEC1_Params</class>
    <class kind="struct">IIMGDEC1_DynamicParams</class>
    <class kind="struct">IIMGDEC1_InArgs</class>
    <class kind="struct">IIMGDEC1_Status</class>
    <class kind="struct">IIMGDEC1_OutArgs</class>
    <class kind="struct">IIMGDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga71491761ce7894192d0953f62e87922e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga31103bf98612d017b2f5c11cc14ac842</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga184dc94b44712d77629d785cefe1398e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC1_Obj *</type>
      <name>IIMGDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8b9b9364f2c4232397b36890618b250e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga7bf45653f5c04d9407d13394663a896c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGENC</name>
    <title>XDM IIMGENC Image Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_e_n_c.html</filename>
    <class kind="struct">IIMGENC_Obj</class>
    <class kind="struct">IIMGENC_Params</class>
    <class kind="struct">IIMGENC_DynamicParams</class>
    <class kind="struct">IIMGENC_InArgs</class>
    <class kind="struct">IIMGENC_Status</class>
    <class kind="struct">IIMGENC_OutArgs</class>
    <class kind="struct">IIMGENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gac529fc95d138993ea754d7ec6018a76c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga784e32991d906518f37e7a5146f5bf13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga827d911bc03c756096d03677ecef5f39</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga04b132637a7c8ee29f0738fce76fed32</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Obj *</type>
      <name>IIMGENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>ga58729c682862e2e74a9b2abb916f4b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c.html</anchorfile>
      <anchor>gabe17217ceb746ff5b0e564a6f3dafa36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IIMGENC1</name>
    <title>XDM IIMGENC1 Image Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</filename>
    <class kind="struct">IIMGENC1_Obj</class>
    <class kind="struct">IIMGENC1_Params</class>
    <class kind="struct">IIMGENC1_DynamicParams</class>
    <class kind="struct">IIMGENC1_InArgs</class>
    <class kind="struct">IIMGENC1_Status</class>
    <class kind="struct">IIMGENC1_OutArgs</class>
    <class kind="struct">IIMGENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9397909ae52d3bb547e18fd8719c333f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga28ded0a8bcf744f7ba289e9b6ae576ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IIMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad065eddb703a62fa12207544e8546f1b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Obj *</type>
      <name>IIMGENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga93fe674dab191daf45489f5bf84134fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IIMGENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga391d9f36711efa2b355c14a03af7abf8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH</name>
    <title>XDM Speech/Voice Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h.html</filename>
    <member kind="enumeration">
      <name>ISPEECH_VoiceMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ga2a5ad3bdafe1e87e2aece51b52700694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_VOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694aabfd422047de38c75ff1caf9f22c7ce0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_UNVOICED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gga2a5ad3bdafe1e87e2aece51b52700694a980404cd1fc1ad41d588319dbe3ed14e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH_CompoundLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>gaed9882c92cb24a565d63fb157a3bc0c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a8913b9e1f47a5e7ab97578c12a115a06</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a254d39814c846c8f5574226162efb458</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h.html</anchorfile>
      <anchor>ggaed9882c92cb24a565d63fb157a3bc0c8a1edb2eb2e360b5292385c671181cfafd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1</name>
    <title>XDM Speech/Voice Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_NullTrafficMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga89ae95d0bce445642cc16c57c0d0968b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968ba87608e5344ca37912234e93b7da59630</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968baa933263447c238bac7df6321e0a11694</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_NULLTRAFFICMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga89ae95d0bce445642cc16c57c0d0968bab4fa5328474e29188aee74797c414aec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_PostFilter</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gac1c8b96d345c0fe4220cdc18669223ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca6f4c302f3c9af56f64806d0861abdd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223acac8e86af79d47c31e04829919bd972705</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_POSTFILTER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ggac1c8b96d345c0fe4220cdc18669223aca37e583ca98bc612bd7dd9c5c451b3cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_VADFlag</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>ga6a40ba3d92ffc5b64a9987f870f57f9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa4d73bb62c3d482112334d7d84cc3cce4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aaa11a5dcd1ae9d5e026cc83cfbb330919</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_VADFLAG_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1.html</anchorfile>
      <anchor>gga6a40ba3d92ffc5b64a9987f870f57f9aa7e66df60583013e51ba279139d13e0b8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_AMR</name>
    <title>XDM Speech/Voice Interface (AMR)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ga566156cfc46f87e73de6bba8eba536c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_4P75</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a99fc4c000b12f09fdcad255694d96d9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P15</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a5e8739090838a47dded4ce9c617b2446</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_5P9</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a633eb6129d753bd00318c91d5c00647d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_6P7</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a61ffd17b289e507380d69e1eca1c2142</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P4</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a45de32cc24a76e2a16bb7f9eecdccb48</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_7P95</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a3d3312de4a395a0a154c13043e6be957</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_10P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a7ca5663dc228a321dff14edaa5887aa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_12P2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9af65cf724c197d3cad7dd932c44e7cba1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gga566156cfc46f87e73de6bba8eba536c9a4943c07dd5924193d6a0a8ce7986c295</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_CodecSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaf6d3e11e5b975770afd11caadcfd8d20</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_PRIMARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20ab414f0b43b46c6407188ab18f07abcd5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_SECONDARY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a06effe2e6cda9dce3ce1773be4a941ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_CODECSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaf6d3e11e5b975770afd11caadcfd8d20a055d66e70f1130f7dd8eab2f05e01e88</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gaeecf736d60bd00c5ac86924b1404ad90</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af79b43d1eb83abaa5510928b71a4abe4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a387c71ba08310d9668dae3883fe3ec28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90af1bbe3a63ca9d6f595b83fa6b91a424c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90a71f0423b70c34ca2afc083e5a62585e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggaeecf736d60bd00c5ac86924b1404ad90aa00c9bc982212f0c55d9f1477bb62ded</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_AMR_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>gabcb3c4ae9c054b69eabd71bde775d86f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD1</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86faf55aa3a28417e1d0da82b546a9b1789d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_VAD2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa35a83e8d85620ee0316880049aef8078</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_AMR_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___a_m_r.html</anchorfile>
      <anchor>ggabcb3c4ae9c054b69eabd71bde775d86fa4789cd0dfd81240681e04f81d7ead9fd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_EVRC</name>
    <title>XDM Speech/Voice Interface (EVRC)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gac0650f1ca8b6e4b6770c038653594633</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a9265da05d970eef081d3dd7ce9dbd4be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633aea1b311ebb57531b23d73857aca828d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggac0650f1ca8b6e4b6770c038653594633a7805bfa6106590db880f7bf892c680d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ga84ecf83f56e51c826bda7095a90b989c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca38d82305bbfabe8919932618e2fdbae3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989cae7259cf80bda232f425379647111b048</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca602b2e9a9e7a1dbaaeafa889230811ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gga84ecf83f56e51c826bda7095a90b989ca1d60ffd9d5228746176eff0117c948fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_EVRC_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>gafe2167d2bb6dc8269af94931fdedc9f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ae8264ae8cb01ccb0953e29e0c3b21cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a8fc2dd52641a64b43d8034b4c0acd1c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a044dbd71700d328377606f5285bdde2a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a7d31d7179ec70e3e28954a6d989d688a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1a5920a92eccc31bc941e54ab46a84a80b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_EVRC_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___e_v_r_c.html</anchorfile>
      <anchor>ggafe2167d2bb6dc8269af94931fdedc9f1ad54aeffbd74c41175c7c3f7d427ad144</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G723</name>
    <title>XDM Speech/Voice Interface (G.723)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G723_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga3a60101c5d140281222eac55ceff3da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_5P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a25ef1e08d5e98120471e2c1526c27d2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_6P3</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a1e8c817ed1c0bdb7fb55444d6e009353</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga3a60101c5d140281222eac55ceff3da7a27554cc9a39b340e0ecd8103719dbffd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G723_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>ga6030020ca3fe69e0d0aaf01728097eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaf62d62d2826cc658130274930660ebb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaeaae41fd25b630c16118a4ffd24276a990</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G723_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g723.html</anchorfile>
      <anchor>gga6030020ca3fe69e0d0aaf01728097eaea889aecb01aca1afc4152f95a8616c147</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_G726</name>
    <title>XDM Speech/Voice Interface (G.726)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_G726_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga5842c3df33b0aec82142cf1fd3ece12e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_16</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ead390f395f226d55baf122302237cdf96</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_24</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eab03a295d41900a44a9c94f3c94baceb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_32</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea769ceb35bd641aac0e5531f1641285ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_40</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12ea8548d58b48b1e6ed42f18024d4793a0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga5842c3df33b0aec82142cf1fd3ece12eac2a351d221bfea5d27b09134cb59e89f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gaa397870da5177152ea1b53fe9e3b6265</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ad0d2189fda7ed821f96577af3b5ba01c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265ada1a67c0602e35ec5c10fba0044d6eae</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a1177bc10761f7968fb1787cf2c5bf599</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ggaa397870da5177152ea1b53fe9e3b6265a386b0d978c9c63729567540b953c7105</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_G726_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>ga889c3788d8981cec15df6971d29306ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaadc717daa84241ac0f3964a2e5a0f564a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPE_RTPSPECIAL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa3e3a96fa9418c89e58ee8dcd75868ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_G726_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___g726.html</anchorfile>
      <anchor>gga889c3788d8981cec15df6971d29306eaa9cfac3209bb22296fa011e0875b37d27</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_PCM</name>
    <title>XDM Speech/Voice Interface (PCM)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_PCM_CompandingLaw</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>ga88faff6d78d80fbb0d3712642a16e1de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_LINEAR</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea9b50f6c66d7d1250dcede6c3076bdd45</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ALAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deaee6ede174249a7ee7b67daccf7437037</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_ULAW</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1deac8a7be49178242066ee82b6800905614</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_PCM_COMPAND_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___p_c_m.html</anchorfile>
      <anchor>gga88faff6d78d80fbb0d3712642a16e1dea5b651f269b71e3d9cfa3fe8e6d494957</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_SMV</name>
    <title>XDM Speech/Voice Interface (SMV)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_NoisePreProc</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gab60bcb3149344cd20bc1d9d1696a208d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da499e6a288509dc326fa6b2a3a211d092</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da5adad45c8630058c96bdafdb030931f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_NSB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208dab44c90dd52dc8fa6cf0c528ffd540e77</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_NOISEPREPROC_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggab60bcb3149344cd20bc1d9d1696a208da39b444aeb37c32f83aee67c415679c04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_VADSelect</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gafb1b4ac5540a4d13c730aaf88dc023be</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea1c29ab48b1ef4af475eb3e95c3e99613</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_VADB</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea6b4ba999b85279488c3db4cae5aee7f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_VADSELECT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggafb1b4ac5540a4d13c730aaf88dc023bea7db43399885c4cf5f1d122913fb1f0ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_TTYMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gad14fd77adfb92f65088ef0b2e6affebd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebdafe82060bfabefca805a51b04c4381003</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_45P45BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda0105f17fb6d97417b56dccc9fde3c73e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_50BPS</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda34cd37f4c8438ade28d24ba1bf3d401b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_TTYMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggad14fd77adfb92f65088ef0b2e6affebda3bbed1bf636d4ccbca35915ca01cff7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DTMFMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga91d61a3a68a62af8f73afb871f1d0d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eabb2bce58703d51269e15c8a9bbbcc11f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_ON</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5ea325b10e0073a2d82e2d272b2dba7149e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DTMFMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga91d61a3a68a62af8f73afb871f1d0d5eafa3d0d05dcad59534119e6d6f60326a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_DataMode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ga9edbd6e156d41f8673e3c26841e4d1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_OFF</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa2c0c4bae0b4e38ec003b221f01bc6c4e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_HALFRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfae9e8887b1b23fc33614aab40523f7f5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_FULLRATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa02c442553dc94438337a7f0b5217d587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_DATAMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gga9edbd6e156d41f8673e3c26841e4d1bfa94de3a5a683830f5e91b1f488a7598d5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_SMV_Mode</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>gae79f94ea770cb63e97b6b08e7021a7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a605f932ca11a86e867b24a87f7c2cb4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a0a3ab57cb83cc3b78664e5f8ee9dc0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_ECONOMY</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a30a76e29dc26f9d6b58461669bbc485f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_CAPACITYSAVE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a3013d7d320c975226bb2785ce39ca852</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_PREMIUM_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a764290efa25fc2f82cba26bed3b788ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_STANDARD_HALFRATE_MAX</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a02765b3d59b321e563dcfb2aefdeb8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_SMV_MODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___s_m_v.html</anchorfile>
      <anchor>ggae79f94ea770cb63e97b6b08e7021a7d8a04f904d973435832277167859b16647b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPEECH1_WBAMR</name>
    <title>XDM Speech/Voice Interface (WBAMR)</title>
    <filename>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</filename>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_PackingType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga8561c34af4f9307ee99eec22b9023da7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_NOCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a0fefa4be1b4fb97d523329d3bbc3d42e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF1_WITHCRC</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a54c89d0a6ae8cb89e5097e39a5e4b06d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_IF2</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a67d42cd4150cd7c05378bc1960a92375</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPE_MIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7acc83cc0d4a577f3f93025e2eff1e2bb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_PACKTYPEFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga8561c34af4f9307ee99eec22b9023da7a568e1ddb1a8b6fff6d9c018c9ac3c7a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPEECH1_WBAMR_BitRate</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>ga60889eeb323f514221f3623e9f749716</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_6P60</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a7821bf03d8f659a4835541eb711741e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_8P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a5109ab789372f28d132350cef02cbe70</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_12P65</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a6cf6726fa2af44d0362bebdbbb05b642</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_14P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a823b5ea1854bf86a1534e790e1410b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_15P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a82efce13fac3031b423f01efa1e00969</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_18P25</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ab306cb8177634d2dadd04c0ab3aadb32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_19P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716abf4b551e950f3dca496dd1781d7d8811</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P05</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716adc1493eee4d5e1df49cade040980d720</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_23P85</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716a45f6d3b08c97d14e0e4017c9328bc965</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPEECH1_WBAMR_BITRATE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_e_e_c_h1___w_b_a_m_r.html</anchorfile>
      <anchor>gga60889eeb323f514221f3623e9f749716ac599e0494b8cbc4788a5abf95232d87f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHDEC</name>
    <title>XDM ISPHDEC Speech/Voice Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_d_e_c.html</filename>
    <class kind="struct">ISPHDEC_Obj</class>
    <class kind="struct">ISPHDEC_Params</class>
    <class kind="struct">ISPHDEC_DynamicParams</class>
    <class kind="struct">ISPHDEC_InArgs</class>
    <class kind="struct">ISPHDEC_Status</class>
    <class kind="struct">ISPHDEC_OutArgs</class>
    <class kind="struct">ISPHDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga1f604442aeef3232e6acc17de9ab51be</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga59bee2fd448023ee04185aaf874cfb45</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga6f7990140490a16e025ffc1d670503a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga48b7104fbe8c5c6cbe2d17b7725e278b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Obj *</type>
      <name>ISPHDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga31722647a0a3b99c36ef57af89d1351a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c.html</anchorfile>
      <anchor>ga73cebce9e1ccbbb0afbb14a4f984a94e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHDEC1</name>
    <title>XDM ISPHDEC1 Speech/Voice Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</filename>
    <class kind="struct">ISPHDEC1_Obj</class>
    <class kind="struct">ISPHDEC1_Params</class>
    <class kind="struct">ISPHDEC1_DynamicParams</class>
    <class kind="struct">ISPHDEC1_InArgs</class>
    <class kind="struct">ISPHDEC1_Status</class>
    <class kind="struct">ISPHDEC1_OutArgs</class>
    <class kind="struct">ISPHDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga87514ee862e0b5a35fcf460a65277a59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga4d2a2279596c72d1d505a94504af9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga712c57b5a16ed53f484260f8ea48c1ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC1_Obj *</type>
      <name>ISPHDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga65c6e2d620b2b46594453ed84ded159f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaef02eb7c18d91b4d4183284c0c4c1d79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHDEC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga80a8f44022a98fb899a102310489ebf9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHGOOD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a1813dc29630e6fd7c6054187077f1b0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDUPDATE</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a10c27d875c65247b78a99e1d28916dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a46a224a6fd50ee1f3fe602c64759c158</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SPEECHLOST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ad7f3cff31625d40f310aaf0a575c1117</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_DEGRADED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9abce8dcb8ad83419dc8225b66d2a36c84</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9ab576985e54ff855753483500e17362ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDFIRST</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a6bcbda5d5df41d58f5a5034fdabffed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_SIDBAD</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a4cf9a9b2ba2919adf36aac69de785623</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHDEC1_FTYPE_ONSET</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_d_e_c1.html</anchorfile>
      <anchor>gga80a8f44022a98fb899a102310489ebf9a0a642d1a2df6645d04a98d198b42a5b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHENC</name>
    <title>XDM ISPHENC Speech/Voice Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_e_n_c.html</filename>
    <class kind="struct">ISPHENC_Obj</class>
    <class kind="struct">ISPHENC_Params</class>
    <class kind="struct">ISPHENC_DynamicParams</class>
    <class kind="struct">ISPHENC_InArgs</class>
    <class kind="struct">ISPHENC_Status</class>
    <class kind="struct">ISPHENC_OutArgs</class>
    <class kind="struct">ISPHENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gaa70981aaff27acca8dc15214ad0538ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga7e16b5ce02a4ae9c232445e1b1628f78</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>gac472f9baf3f8de53cfef7d83a05df2fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga3769ec58a3fb188995557ab5f4986a0a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Obj *</type>
      <name>ISPHENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga53d4faeb65284507a1eab034036a11ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c.html</anchorfile>
      <anchor>ga835dc5261cc96bd0c6a77c1b33f5f197</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_ISPHENC1</name>
    <title>XDM ISPHENC1 Speech/Voice Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</filename>
    <class kind="struct">ISPHENC1_Obj</class>
    <class kind="struct">ISPHENC1_Params</class>
    <class kind="struct">ISPHENC1_DynamicParams</class>
    <class kind="struct">ISPHENC1_InArgs</class>
    <class kind="struct">ISPHENC1_Status</class>
    <class kind="struct">ISPHENC1_OutArgs</class>
    <class kind="struct">ISPHENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga332d5aa164c31b5681b2cea91d7e5016</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga22ade7510d7d35abb25a60b64f44a92d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8f31ee15e0081314b41914efc29c5a9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ISPHENC1_ENOOUTPUT</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa82f51e92fce79e8c507771c443b3e35</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Obj *</type>
      <name>ISPHENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga995e9ed220499520c23c0df118d7acd8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>ISPHENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga16523cd9d058f54acb8f5d1bd4bd5d97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>ISPHENC1_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e6571f54c1264844aa2c0e05119a624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SPEECH</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624ae24818a9a9b1a23146162bb950ab035a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_SIDFRAME</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624aa8c57b4e299ff4038b40a5911eff281d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ISPHENC1_FTYPE_NODATA</name>
      <anchorfile>group__ti__xdais__dm___i_s_p_h_e_n_c1.html</anchorfile>
      <anchor>gga8e6571f54c1264844aa2c0e05119a624a6e2c23204ce4ae3dd2001aa610644638</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IUNIVERSAL</name>
    <title>XDM Beta Universal Algorithm Interface</title>
    <filename>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</filename>
    <class kind="struct">IUNIVERSAL_Obj</class>
    <class kind="struct">IUNIVERSAL_Params</class>
    <class kind="struct">IUNIVERSAL_DynamicParams</class>
    <class kind="struct">IUNIVERSAL_InArgs</class>
    <class kind="struct">IUNIVERSAL_Status</class>
    <class kind="struct">IUNIVERSAL_OutArgs</class>
    <class kind="struct">IUNIVERSAL_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga27f56f76d4fd15aa0d7e0ebbcb861d4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gad0ebbb98143ab6995c1268efa4cbf150</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IUNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gacb40d81bebf31e7de2267d6cb9bde3a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Obj *</type>
      <name>IUNIVERSAL_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa47732c807c80b94d7f29cf72d9ed694</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IUNIVERSAL_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga17756fe87be378872a1647a668f18c9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDANALYTICS</name>
    <title>XDM Beta Video Analytics Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</filename>
    <class kind="struct">IVIDANALYTICS_Grid</class>
    <class kind="struct">IVIDANALYTICS_Rule</class>
    <class kind="struct">IVIDANALYTICS_Obj</class>
    <class kind="struct">IVIDANALYTICS_Params</class>
    <class kind="struct">IVIDANALYTICS_DynamicParams</class>
    <class kind="struct">IVIDANALYTICS_InArgs</class>
    <class kind="struct">IVIDANALYTICS_Status</class>
    <class kind="struct">IVIDANALYTICS_OutArgs</class>
    <class kind="struct">IVIDANALYTICS_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaf9760765b216cdbc5079be6e1904b795</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac314c2ce1b08297ccfbf0c63dc3a257c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaebc9260d46c5e53d35bb4f5f100b96ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_SETRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3d56d0f1a5afc78401314d4fdee63dc2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_CLEARRULE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga44579981d799141f6e0368acf999b8e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXTARGETS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade504e11b8b0bc9e3925640b2cafebd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDANALYTICS_MAXEVENTS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa71cddcd1d8b054c48f9966866e386b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Obj *</type>
      <name>IVIDANALYTICS_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga26ad8d51394ef852e42cc1c4948de0eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5be3d2530a181c9826dc4c3322344132</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_AnalysisMask</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga4a8b524c62f02622465884156f2c6f59</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_MOTIONDETECT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59a3cad03f6d20ecbdc0103df4e73101e47</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTRACKING</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59ad6da9e357c2c7721f04b1ff5beb38929</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga4a8b524c62f02622465884156f2c6f59af48becd353153ab4285b4305d3467624</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ObjectType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga40e54ed88eb97360b4ca8f244c2b9f62</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_VEHICLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad9daa80daa5e20d4c010d577a7347918</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_HUMAN</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ad82eb960014d7ede011678c5705ee1ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_OBJECTTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga40e54ed88eb97360b4ca8f244c2b9f62ab6cd25f42da6d9e7e43ebb4ce272cf97</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ActionType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga47e8c8886c5d35981380c922db1eeab4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_LOITER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aba5736e40d9f5ab0ff2590d66e04edc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_ENTER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a86e2c5b11a0e4c20d245cb6de0cf8bb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_EXIT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4af0f133918f8b9575ca32e05f512270a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_APPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a681d3cbb139a67f813899f0be3250f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_DISAPPEAR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a570191d5b93ea4345fb5bcb91f3a4d52</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSL2R</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a25a21e42fece6687a27205a828e025e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSR2L</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4aa4df30a99741c60e039d8042476922c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSU2D</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a82b0a4cbd8efa23126decf532abcf6e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_CROSSD2U</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a899876b69418a4b7187e73a1fd22e0a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_ACTIONTYPE_USERBASE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gga47e8c8886c5d35981380c922db1eeab4a20b606cf024b3812694d53e0f9985cde</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDANALYTICS_ViewState</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gab02bfb6a7b2a76eac00f1bb7d3801662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_BAD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a42c1e0003605067a4def8cfd4c061dba</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDANALYTICS_VIEWSTATE_GOOD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ggab02bfb6a7b2a76eac00f1bb7d3801662a093b1e31c7bb032707492cfe72cd8fe8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC</name>
    <title>XDM IVIDDEC Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c.html</filename>
    <class kind="struct">IVIDDEC_Obj</class>
    <class kind="struct">IVIDDEC_Params</class>
    <class kind="struct">IVIDDEC_DynamicParams</class>
    <class kind="struct">IVIDDEC_InArgs</class>
    <class kind="struct">IVIDDEC_Status</class>
    <class kind="struct">IVIDDEC_OutArgs</class>
    <class kind="struct">IVIDDEC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gafa63f96dc4a5430e21a8454a609fe205</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3fc5e8b896808e13dc4a1dd037592c61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f3f0d74b7b4895adc3601998895b930</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3ff96fb69baef4d04b31682234957de1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Obj *</type>
      <name>IVIDDEC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>gabc249717018b892fafca9425887b7464</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7f8d05603824403adb994fe59d55bdcd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC1</name>
    <title>XDM IVIDDEC1 Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</filename>
    <class kind="struct">IVIDDEC1_Obj</class>
    <class kind="struct">IVIDDEC1_Params</class>
    <class kind="struct">IVIDDEC1_DynamicParams</class>
    <class kind="struct">IVIDDEC1_InArgs</class>
    <class kind="struct">IVIDDEC1_Status</class>
    <class kind="struct">IVIDDEC1_OutArgs</class>
    <class kind="struct">IVIDDEC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaee746b34bc5327d7755c36e9dbb93f99</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gac76d0185e99e4dfb7d33f8b06d73a731</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga8c35fdf3e5022078dfee9064ac08f52a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC1_FREE_BUFF_SIZE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaf9fd4bffd14decc067ecf3f2c486605e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Obj *</type>
      <name>IVIDDEC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga3470ccaa78e2f267e1b8e08c7ae25455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga88cf5de26dfa5e05400b2d6e25ea027d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC1_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga499b0864c81e20998f743b9e834e10c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a9fb1a3543d4c48a7c5a7cf9242058746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6a3a281632bb399cb0c73a18ebff327706</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c1.html</anchorfile>
      <anchor>gga499b0864c81e20998f743b9e834e10c6aebd67fc7b931e0796cfa9a970137b12a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDDEC2</name>
    <title>XDM IVIDDEC2 Video Decoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2_Obj</class>
    <class kind="struct">IVIDDEC2_Params</class>
    <class kind="struct">IVIDDEC2_DynamicParams</class>
    <class kind="struct">IVIDDEC2_InArgs</class>
    <class kind="struct">IVIDDEC2_Status</class>
    <class kind="struct">IVIDDEC2_OutArgs</class>
    <class kind="struct">IVIDDEC2_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaf8c9523a27942aa46eba097398a0e49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac1f0ebc291c92f796a5144fa57f7390f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7c8386cbcd58bcb8a16e15df6587f3f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gafa7a5979f7945ff9ce5822c8f5fa57d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2_Obj *</type>
      <name>IVIDDEC2_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gab044a3dd5967ff04c487062ed0586c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDDEC2_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8b9180923c067cbb47115d18189501c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDDEC2_FrameOrder</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga31f21bf0ec796b5506cd8a0f0cf7710f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DISPLAY_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa4dc184c19c62190e5f933e46e5bccc2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_DECODE_ORDER</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa33ea07222ede0a10cb27bad4b9db445d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDDEC2_FRAMEORDER_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gga31f21bf0ec796b5506cd8a0f0cf7710fa3599bb4a0d320e3e36d2aa49a7ae79e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDENC</name>
    <title>XDM IVIDENC Video Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_n_c.html</filename>
    <class kind="struct">IVIDENC_Obj</class>
    <class kind="struct">IVIDENC_Params</class>
    <class kind="struct">IVIDENC_DynamicParams</class>
    <class kind="struct">IVIDENC_InArgs</class>
    <class kind="struct">IVIDENC_Status</class>
    <class kind="struct">IVIDENC_OutArgs</class>
    <class kind="struct">IVIDENC_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_CID</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaeba527be430e1584897bc410ef06e08a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf31926403a1beba354092c33e6f8f41f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf0d8e925b556bc7d992afb7dc9005fe7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gaf08f3e2a75c1e39a184835d0683ca88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Obj *</type>
      <name>IVIDENC_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>gafe560b65239e58d0a48897db58ee33f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c.html</anchorfile>
      <anchor>ga13eaed2bcde87e35269eed69590e2313</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDENC1</name>
    <title>XDM IVIDENC1 Video Encoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</filename>
    <class kind="struct">IVIDENC1_Obj</class>
    <class kind="struct">IVIDENC1_Params</class>
    <class kind="struct">IVIDENC1_DynamicParams</class>
    <class kind="struct">IVIDENC1_InArgs</class>
    <class kind="struct">IVIDENC1_Status</class>
    <class kind="struct">IVIDENC1_OutArgs</class>
    <class kind="struct">IVIDENC1_MbData</class>
    <class kind="struct">IVIDENC1_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf7b49aed126ab846bbcff9bb2d481533</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8022d457cb04187a3b1a055eaa2d1629</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga1623748edce151d19caed068981773f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Obj *</type>
      <name>IVIDENC1_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga953dc9cc5ece87d8b371bd2adbb5082f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDENC1_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2654e133ba490dec6e8dfa56d1b633ef</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDTRANSCODE</name>
    <title>XDM IVIDTRANSCODE Video Transcoder Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</filename>
    <class kind="struct">IVIDTRANSCODE_Obj</class>
    <class kind="struct">IVIDTRANSCODE_Params</class>
    <class kind="struct">IVIDTRANSCODE_DynamicParams</class>
    <class kind="struct">IVIDTRANSCODE_InArgs</class>
    <class kind="struct">IVIDTRANSCODE_Status</class>
    <class kind="struct">IVIDTRANSCODE_OutArgs</class>
    <class kind="struct">IVIDTRANSCODE_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga69d74b9dad25f19d864771f9d81a9a6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga29ec01f0e1dea7abff118a9cf8792885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaf6e122d808cecd873a7f51e34c2fb4b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IVIDTRANSCODE_MAXOUTSTREAMS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9b9cc80049e4cebea89e7c4cf58d426c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Obj *</type>
      <name>IVIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga049f5b53ee2c04135a1ff19afbc215c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IALG_Cmd</type>
      <name>IVIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gab5d20cf8d615294c7912796b79f85f5f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_IALG</name>
    <title>IALG - XDAIS Algorithm Interface</title>
    <filename>group__ti__xdais___i_a_l_g.html</filename>
    <class kind="struct">IALG_MemRec</class>
    <class kind="struct">IALG_Obj</class>
    <class kind="struct">IALG_Params</class>
    <class kind="struct">IALG_Status</class>
    <class kind="struct">IALG_Fxns</class>
    <member kind="define">
      <type>#define</type>
      <name>IALG_DEFMEMRECS</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga8a220fa863380937542f6a38be47ceda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_OBJMEMREC</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga0e3202a4d8dc0bd3cb300633922ffd54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_SYSCMD</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga200f155f9e2720011270e99f17bb6675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EOK</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga2c15898121a23a164e4ea2bcc4f7e7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_EFAIL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga604e5600815cbd58846e0c5c05b6ba18</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILBASE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga1f655af6b5ce37aaf5328243d1993cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_CUSTOMFAILEND</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafbab7f3470d8b5a46615f1aca5c739b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga86018453b8f991c8cb545b2e43c80c9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_MXTRN</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gafc53b940e2982a2e859bda0555180eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isProg</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga93e8704d8e88d2f3dde1a85317232b59</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IALG_isOffChip</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gae2530ce6b07542f579871961a3fcfd4f</anchor>
      <arglist>(s)</arglist>
    </member>
    <member kind="typedef">
      <type>struct IALG_Obj *</type>
      <name>IALG_Handle</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga16c037803ea218ba3dc5158f55ef27c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>unsigned int</type>
      <name>IALG_Cmd</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga9032f20923ef2ba1d6b88c87a20075fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemAttrs</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga805f1c1330403c05633277a073862e3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SCRATCH</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da85e0509f7e82ebd01b57f899122de9b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_PERSIST</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da68adbe0194074e0474333b76f7d1e090</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_WRITEONCE</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga805f1c1330403c05633277a073862e3da42356e6aa11869bfd15f31472f49a7c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IALG_MemSpace</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>ga262eb64dc7343999fa07d535ae163497</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6410b22d1d073ab55b289ca2f3c03b35</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_IPROG</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a946577db145f691f81d7085fc51e2201</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_ESDATA</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a85fff905ed5e83445e3424ce5ba03175</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_EXTERNAL</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa98151c21c55ddaf8c1918d8007e5493</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497af6a85bf972a4d090e2c0e4d31565f879</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497ad7b3b18fc0263be0f0702d263f600d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497aa5c6d8cfdb63c11fafd22bb87204c5cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM0</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4b31d959f6af27a012a87957c05d9c4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM1</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a4ac938c5e58e4d4a30458b63869f0095</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_DARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a17fc19eac565b29871efbfed54760414</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IALG_SARAM2</name>
      <anchorfile>group__ti__xdais___i_a_l_g.html</anchorfile>
      <anchor>gga262eb64dc7343999fa07d535ae163497a6db79aaafcf9b4354f2828c2a94b8590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_dsplink_utils_ladclient</name>
    <title>LAD Communication Interfaces</title>
    <filename>group__ti__dsplink__utils__ladclient.html</filename>
    <class kind="struct">LAD_DspStatus</class>
    <member kind="define">
      <type>#define</type>
      <name>LAD_MAXLENGTHIMAGENAME</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga8e07e54d7aea12d190555cf31db17c7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LAD_MAXLENGTHCONFIGNAME</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga901a4242cb9df3d3c2c302f4d9c7e6e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uns</type>
      <name>LAD_ClientHandle</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gab2c7f70765d4bd228dab4533b09b71e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>LAD_Status</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga66608549d1df270be82121e78bedfda1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_SUCCESS</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a5802b07b46745ac8f39998db29cc2249</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_FAILURE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a1319915bffee06594ea9ba14b391e331</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_INVALIDARG</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a87a9a89db556994e101dba2970d7364c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_ACCESSDENIED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1aabd0ac5be9c88df2e212f56969fc1568</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_ALREADYRUNNING</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1aaf4de0b0d821d54271116e7bfd9940ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STILLRUNNING</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1ab3bb8044e7eea1d1edcb515268b6f3cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_IOFAILURE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a2a42d4f645ae6a4d5169da7d05333124</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_NOTCONNECTED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a9d549f85bd6bf35bd8cd8631257af09f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_INVALIDVERSION</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gga66608549d1df270be82121e78bedfda1a139300fdb548633dd734a3b9edafe9f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>LAD_DspState</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gaa4571d04b2df6dbc63ef29617272e22a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_UNKNOWN</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa66542229d94a84789da0b2a77b082124</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_SETUP</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa686d5fffa5c19ae9252f25fb7b73ebb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_LOADED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aafc9b72be215e0669435e6ab62961c2eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STARTED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa68ab6fef84749e86c15294c1ca68f051</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_STOPPED</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa22795295bdd8124ac776b031d568c5ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_IDLE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aadd33b67055b31bf478ca9c0ab654ed08</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_RESET</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aa1cc66b69fb539f224d959d49c5bfc792</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LAD_UNAVAILABLE</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ggaa4571d04b2df6dbc63ef29617272e22aac01999184a3b1c65950843831a271b60</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_connect</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga1296ebdb60b7bba19643006635075af5</anchor>
      <arglist>(LAD_ClientHandle *handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_disconnect</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gababa518d4fe889e45400f80b4855802e</anchor>
      <arglist>(LAD_ClientHandle handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_getDspStatus</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>gafb7216195e4cf5f94f99f171f75e74e8</anchor>
      <arglist>(LAD_ClientHandle handle, Int cpuId, LAD_DspStatus *statusInfo)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_releaseDsp</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga30ecbd942631db0ae030c78ba23387d9</anchor>
      <arglist>(LAD_ClientHandle handle)</arglist>
    </member>
    <member kind="function">
      <type>LAD_Status</type>
      <name>LAD_startupDsp</name>
      <anchorfile>group__ti__dsplink__utils__ladclient.html</anchorfile>
      <anchor>ga48bcbafcd3534ad79b31f09c8e99df1f</anchor>
      <arglist>(LAD_ClientHandle handle, Int cpuId, String linkConfigName, String imageName)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>AUDDEC</name>
    <title>AUDDEC Audio Decoder Interface</title>
    <filename>group___a_u_d_d_e_c.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_EOK</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5aadb97b6280f6e82207dae35a19ab75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_EFAIL</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gac525735408fd0a7afd12dd377bbf060d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_ERUNTIME</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gae83a152915d35026cdb65751ed07348a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_ETIMEOUT</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga27ab905518ac056065d4b88bce101885</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC_FOREVER</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga68744c319229a47b80856511a560ce56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_Status</type>
      <name>AUDDEC_Status</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0d82470b3aa6bc16eb5ac0667e43a611</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDDEC_Handle</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga9a4e2b0c3961b3ca9963bd53394f5376</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC_Params</type>
      <name>AUDDEC_Params</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gaf6b50d59060abcc0f793f30860cdc1fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_InArgs</type>
      <name>AUDDEC_InArgs</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gaa7db0270c5e9c3f5f96e20044e22e715</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_OutArgs</type>
      <name>AUDDEC_OutArgs</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gadd938b8170a9e1b1b599035bb5918917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_Cmd</type>
      <name>AUDDEC_Cmd</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga90e760cacdf6a9ea4c15a9a8952a5fb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC_DynamicParams</type>
      <name>AUDDEC_DynamicParams</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga050b8f4d86a988ad5315a053cf2e623e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>AUDDEC_Handle</type>
      <name>AUDDEC_create</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>gae6ed4b3e8a66743baf5a4ae65e382318</anchor>
      <arglist>(Engine_Handle e, String name, AUDDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC_process</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga5f07d733ba7987df8a334263fc01113e</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC_control</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga2f774103e5122bf6cfa0cccb7b2bccdb</anchor>
      <arglist>(AUDDEC_Handle handle, AUDDEC_Cmd id, AUDDEC_DynamicParams *params, AUDDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDDEC_delete</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga0ab1678bca5777911d621676f7ecf202</anchor>
      <arglist>(AUDDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDDEC_processAsync</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga429d9453059105c64cdd62258ee4bda1</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDDEC_processWait</name>
      <anchorfile>group___a_u_d_d_e_c.html</anchorfile>
      <anchor>ga07f8e317523dcaf9dfe58ebe56b53685</anchor>
      <arglist>(AUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDDEC_InArgs *inArgs, AUDDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>AUDENC</name>
    <title>AUDENC Audio Encoder Interface</title>
    <filename>group___a_u_d_e_n_c.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_EOK</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga4c5cbf3bf71fcbc6bbf29f1f32fdf852</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_EFAIL</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gad908fbd7c4b483bfa39be10b9c834ce9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_ERUNTIME</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf875d4b5e97d143e8d882801bf7c88dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_ETIMEOUT</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gacd92898b4599b439cfd3228b29220696</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC_FOREVER</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga5ca7c02759b1a62dc67b8d30cdd9f0e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_Status</type>
      <name>AUDENC_Status</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga7d46b31739a556dd457b7ab32764788b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDENC_Handle</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga855d8e711a8401f488094e2ec7efcd51</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC_Params</type>
      <name>AUDENC_Params</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga45a398c8eecb36cff04ebeecf3dbd258</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_InArgs</type>
      <name>AUDENC_InArgs</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga08bdf4d2128042a91f7b5abee25f5671</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_OutArgs</type>
      <name>AUDENC_OutArgs</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gab58c6abd4ac79581f24335f3392ccee3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_Cmd</type>
      <name>AUDENC_Cmd</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaf6be17656a84026d539cbc9206c2640f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC_DynamicParams</type>
      <name>AUDENC_DynamicParams</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga595199f736ff81270764c1e2073c119c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>AUDENC_Handle</type>
      <name>AUDENC_create</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga7bd1200782629a1654c47a49b0afbbcc</anchor>
      <arglist>(Engine_Handle e, String name, AUDENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC_process</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>ga2a80fee7800e81fee57d2797a8759e2d</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, AUDENC_InArgs *inArgs, AUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC_control</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaeff5234573e4c2aa429164c28772fdd0</anchor>
      <arglist>(AUDENC_Handle handle, AUDENC_Cmd id, AUDENC_DynamicParams *params, AUDENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDENC_delete</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaaca35ba0e092775f695cdfafd975a222</anchor>
      <arglist>(AUDENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDENC_processAsync</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gaaeddbf9dd9c4d6690c2dbb2732d2d262</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>AUDENC_processWait</name>
      <anchorfile>group___a_u_d_e_n_c.html</anchorfile>
      <anchor>gac3d34c85e0d4859b8f45fa76445ce7e6</anchor>
      <arglist>(AUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_audio1_AUDDEC1</name>
    <title>AUDDEC1 Audio Decoder Interface</title>
    <filename>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga7cae0178b745ced9741f73c78b14cc59</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga7b362018715454a7cd69d3852a45713c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga897c4f1874face10e1445ac6bf6e0610</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga367a626a0619b14d2bf621017ba5489d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9c3af29d4795a05bcf8312f79614cfbd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga1f8a3080f30308909e6a16e935cddc77</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDDEC1_Params</type>
      <name>AUDDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga9f31560ab1264f8819e828a05b1ede43</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_InArgs</type>
      <name>AUDDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gacaf3e3bbdafd81372ae2a5ad2b62f043</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_OutArgs</type>
      <name>AUDDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaddc74dbbd57b740bd39747df2b7c8b88</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_Cmd</type>
      <name>AUDDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga3a5878eef18304b679d71bba5ccbdb2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_Status</type>
      <name>AUDDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga0d7173984244221930950e73fede03fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDDEC1_DynamicParams</type>
      <name>AUDDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga459675fe5d579d089e3dabac96c2decc</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gad6a763c59bef6cbbf42229fadd59996c</anchor>
      <arglist>(AUDDEC1_Handle handle, AUDDEC1_Cmd id, AUDDEC1_DynamicParams *params, AUDDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>AUDDEC1_Handle</type>
      <name>AUDDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gaea018c45115cbd0a8770533652d64605</anchor>
      <arglist>(Engine_Handle e, String name, AUDDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga598c49e01a1bb081056878ff684c255d</anchor>
      <arglist>(AUDDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga6c56308ce43be75e9bfde187d3cf9857</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>gac3be9dd65f18ca77540104e729c75492</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_d_e_c1.html</anchorfile>
      <anchor>ga4e96ed949f9e2e895e9b7af97da64472</anchor>
      <arglist>(AUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDDEC1_InArgs *inArgs, AUDDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_audio1_AUDENC1</name>
    <title>AUDENC1 Audio Encoder Interface</title>
    <filename>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad041cdb795eb67ed045070f3a5b8e02f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab7afa90b2e5f36f30e5bb40d47ed3a47</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad1884d423418d2ab65fc68e53b852d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab33f23be8d3ccc4359abe5e5b40339e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>AUDENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga69188768596074074cd78e022b82cc74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>AUDENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga8ea092f42c3ab3ae85939be5665cf6ef</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IAUDENC1_Params</type>
      <name>AUDENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga65c939059ccca8d6ae568d1f74d90d82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_InArgs</type>
      <name>AUDENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga2acdfe2b6adcdef65eeae4117b4b5c0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_OutArgs</type>
      <name>AUDENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga68ea1073c2c7a63a3ae592ee863a6d66</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_Cmd</type>
      <name>AUDENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga11153a4a24f6302e33a4864182f3aadc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_Status</type>
      <name>AUDENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gafd9444abf1e55e5f485be698c6c2d32d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IAUDENC1_DynamicParams</type>
      <name>AUDENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga067151e76cb3a8b3280c19d53e2b1b77</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_control</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gab51d1cb8d0eaf13f828d8b1da4cc35b6</anchor>
      <arglist>(AUDENC1_Handle handle, AUDENC1_Cmd id, AUDENC1_DynamicParams *params, AUDENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>AUDENC1_Handle</type>
      <name>AUDENC1_create</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gad20840f08b1d1c665ff274a94548bc4a</anchor>
      <arglist>(Engine_Handle e, String name, AUDENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>AUDENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga12b1afd6e52710a3b7c9e7f89fc552bf</anchor>
      <arglist>(AUDENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_process</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga3bd9752523d729a6ccfe4bd9e554e55a</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>gaafc736b175b11fd5b7a05e5dbc8c37a1</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>AUDENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__audio1___a_u_d_e_n_c1.html</anchorfile>
      <anchor>ga499821481f85edc25d6e7295a2417231</anchor>
      <arglist>(AUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, AUDENC1_InArgs *inArgs, AUDENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>IMGDEC</name>
    <title>IMGDEC Image Decoder Interface</title>
    <filename>group___i_m_g_d_e_c.html</filename>
    <class kind="struct">IIMGDEC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_EOK</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga18265bf93b5508740ac1b3d546f1cb75</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_EFAIL</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2f4ee615a65c5dcc72cfe57997426723</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_ERUNTIME</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gadd2ba1d0e893b1b5f5b1e933ad492675</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_ETIMEOUT</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga2c60d166796461a4e9ee4ef554419fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC_FOREVER</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga8b51e0e9bfa3b6aee4f4d7bf9caf36a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_Status</type>
      <name>IMGDEC_Status</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga58ebb7923343f50683714a7463933e11</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGDEC_Handle</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga0768d267cc9be1cda691a0fae30655a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGDEC_Params</type>
      <name>IMGDEC_Params</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga60f2242db982a2a69f1c025bf4f708e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_InArgs</type>
      <name>IMGDEC_InArgs</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gae0939dc64e3ea2514c48a8af19d9a3f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_OutArgs</type>
      <name>IMGDEC_OutArgs</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gaf78b37f058a09beebb599bc4ead7441e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_Cmd</type>
      <name>IMGDEC_Cmd</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga89ac4c1fae57006371ee38bc87a00be7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC_DynamicParams</type>
      <name>IMGDEC_DynamicParams</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga1610026234cd8732f5c3664ea77371ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>IMGDEC_Handle</type>
      <name>IMGDEC_create</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga7bf438523b872178bb45c124f831c551</anchor>
      <arglist>(Engine_Handle e, String name, IMGDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC_process</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga80cec6e31f11193684534228890443c1</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC_control</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga361f5d57077f48fc9741834baf839e15</anchor>
      <arglist>(IMGDEC_Handle handle, IMGDEC_Cmd id, IMGDEC_DynamicParams *params, IMGDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGDEC_delete</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>ga4a99768e5cf0e3e1009610c1129980ca</anchor>
      <arglist>(IMGDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC_processAsync</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gaed139e4f01252d64cd455180bf77fff4</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC_processWait</name>
      <anchorfile>group___i_m_g_d_e_c.html</anchorfile>
      <anchor>gad6c4ce38e17925aa2ef88d0840b5b6ae</anchor>
      <arglist>(IMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGDEC_InArgs *inArgs, IMGDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>IMGENC</name>
    <title>IMGENC Image Encoder Interface</title>
    <filename>group___i_m_g_e_n_c.html</filename>
    <class kind="struct">IIMGENC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_EOK</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga3fddab07429ce18f219c808a9636c1c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_EFAIL</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga1035fa201d367beaa01171d3702d3c89</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_ERUNTIME</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga7468e67ebca1c5089a98176081fe3a58</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_ETIMEOUT</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga4bc59bd8632e0441adfe8026aedff4c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC_FOREVER</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gacadfe8b4b15c7d2ed88b7a78f6b8581f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_Status</type>
      <name>IMGENC_Status</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gae1cd05f2a14905e9f0578c23954addf7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGENC_Handle</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga13eca575480879d3df31e1a2d588b43a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC_Params</type>
      <name>IMGENC_Params</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga20b07e44e01e327926ea8c41f1876729</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_InArgs</type>
      <name>IMGENC_InArgs</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gac3b9b18dbb0a8cc69dbfcf66b2ac886d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_OutArgs</type>
      <name>IMGENC_OutArgs</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga0412ae052b70d1e648e9cc55e6edb5f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_Cmd</type>
      <name>IMGENC_Cmd</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gaedbc4d6f51636441aefd18ee97169fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC_DynamicParams</type>
      <name>IMGENC_DynamicParams</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gab301d74ca14ca7db405477ca3f0e24ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>IMGENC_Handle</type>
      <name>IMGENC_create</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga9628ee04bd5ef12f6972dc1708237677</anchor>
      <arglist>(Engine_Handle e, String name, IMGENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC_process</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gae4bb1eb7c6c7625da250eeafab35ff06</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IMGENC_InArgs *inArgs, IMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC_control</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga5183342c7640653294da59dc59041212</anchor>
      <arglist>(IMGENC_Handle handle, IMGENC_Cmd id, IMGENC_DynamicParams *params, IMGENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGENC_delete</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga92c2bcf19de0ae718d0229de853d85c5</anchor>
      <arglist>(IMGENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC_processAsync</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>ga3f20ac89181a99022e282c24bd0c4a57</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC_processWait</name>
      <anchorfile>group___i_m_g_e_n_c.html</anchorfile>
      <anchor>gab123ef1a678725fafd78bc68dd620f14</anchor>
      <arglist>(IMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_image1_IMGDEC1</name>
    <title>Image decoder codec interface</title>
    <filename>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</filename>
    <class kind="struct">IIMGDEC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gadad666bc5dc5da3d800148989639327e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga1e275de814f6d8642258c68a3136b75e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga90b7f2c50ad51a88787996590fa77ef0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga8805b253e0336884dca9e56ddd530634</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gab30e34559cc8849c8effbe6ec5f541e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gacf60594a88881713b025cf2d9fc22c82</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Params</type>
      <name>IMGDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga6cc479787ad5fbd119eaebdec9ebc333</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_InArgs</type>
      <name>IMGDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gada90b2b2359f429e8eef0d3a5ed66715</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_OutArgs</type>
      <name>IMGDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabf54904c6c64d848e8a325e2456e6c22</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Cmd</type>
      <name>IMGDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga6f8a6dde7d6d121eadb391ad2b18e97e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_DynamicParams</type>
      <name>IMGDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga59288a5b06a9770227c78de934e525b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGDEC1_Status</type>
      <name>IMGDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gac9bc559efa5ef1fcddd0cc4c3ce6d2fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga83c6818a0b02f0ca06115d4258c6ede9</anchor>
      <arglist>(IMGDEC1_Handle handle, IMGDEC1_Cmd id, IMGDEC1_DynamicParams *params, IMGDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IMGDEC1_Handle</type>
      <name>IMGDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga66558eda5ac60a94c643533277c15d79</anchor>
      <arglist>(Engine_Handle e, String name, IMGDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga97e6f62e2348dfc73fd720e26a0092f5</anchor>
      <arglist>(IMGDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga320bcaf531f5561c3a27a60ad7136b58</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>ga21b9f33a3da90adc8f896ad8edbc78b1</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_d_e_c1.html</anchorfile>
      <anchor>gabfc0a347e34e33701dc36f32da2d39fc</anchor>
      <arglist>(IMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGDEC1_InArgs *inArgs, IMGDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_image1_IMGENC1</name>
    <title>Image encoder codec interface</title>
    <filename>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</filename>
    <class kind="struct">IIMGENC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga57670039c8686c8516f5cadc88e41cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gac7c0b09a9f97584f1f5670297bc99505</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae0706d2612934f3195b096f2bfe8be83</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga8ba470948d353c973c2c44c0fa016040</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>IMGENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga0e40a27ad4939058690c0be561c5d7b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>IMGENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga25441483c5175bef9cc003ccb591a0f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IIMGENC1_Params</type>
      <name>IMGENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9c6dca09ddb4457155309d9259f195f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_InArgs</type>
      <name>IMGENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga1d82fa42f9a18951bcb217bf90daad30</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_OutArgs</type>
      <name>IMGENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gafd2a75a9ae2c88d7771c146816545dc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_Cmd</type>
      <name>IMGENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga70cb858c6f18680aae37732b1efb4ec4</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_DynamicParams</type>
      <name>IMGENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gad7fae9fdd89a9d45701cc449d92e0dc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IIMGENC1_Status</type>
      <name>IMGENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga9c88d92cdf6078a11f7dfe151eeb0cc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC1_control</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga5f7473a42611fa3527c9293a31a90ca6</anchor>
      <arglist>(IMGENC1_Handle handle, IMGENC1_Cmd id, IMGENC1_DynamicParams *params, IMGENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>IMGENC1_Handle</type>
      <name>IMGENC1_create</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gae662096fff942c48b7cb9632c462365c</anchor>
      <arglist>(Engine_Handle e, String name, IMGENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>IMGENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga929b104c6d4aae0f1002c0c92c0b0abb</anchor>
      <arglist>(IMGENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>IMGENC1_process</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gacb34e6495073f40e06282bb17b394e06</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IMGENC1_InArgs *inArgs, IMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>gac997094b38bd65e1bfcf9f9af0f515f4</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>IMGENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__image1___i_m_g_e_n_c1.html</anchorfile>
      <anchor>ga933289ef04af9d63a903edf11eeca274</anchor>
      <arglist>(IMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_osal_Memory</name>
    <title>Codec Engine OSAL - Memory</title>
    <filename>group__ti__sdo__ce__osal___memory.html</filename>
    <class kind="struct">Memory_AllocParams</class>
    <member kind="define">
      <type>#define</type>
      <name>Memory_DEFAULTALIGNMENT</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gad3f3ab6aee96704cc82d79d8a3bb08a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_GTNAME</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga32a55c886c1233d7d3c865f57a5d8af7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_CACHED</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gaea7736ca0f8d012d8d0813a4e2871c64</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_NONCACHED</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga69466f2d58c621b9b1a8801d0de41b3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Memory_CACHEDMASK</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga0652dc1abbd60b09a391adb9f8e0ae32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Memory_type</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gac2a14a66c71e5108d4b029a2e0d940c9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_MALLOC</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9af1d579534634486f6806cba8f5533279</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_SEG</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a1138288e1138d0608c8c525af37b6fec</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_CONTIGPOOL</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a3b7e6ba0d9c2794302f897e423a5ed50</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Memory_CONTIGHEAP</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ggac2a14a66c71e5108d4b029a2e0d940c9a69776699cf99579da5bd02c9ff7e0031</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_alloc</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gad526de48c332226c46d312a512566a09</anchor>
      <arglist>(UInt size, Memory_AllocParams *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheInv</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gaf371d3bc92479fb36123670b223211ff</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheWb</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga5bf0f4cf9af5933dd7f9d2e486813ae4</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_cacheWbInv</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga8ae58d5c6b83c607b925d41edd80f0b5</anchor>
      <arglist>(Ptr addr, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_contigAlloc</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gadcc65a14970757fbb5bc4ff4e9730701</anchor>
      <arglist>(UInt size, UInt align)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>Memory_contigFree</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gae8e4e295e8faf95b92cc0886aa14c978</anchor>
      <arglist>(Ptr addr, UInt size)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>Memory_free</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga6f97024ed8b8da994a729ab87cc26c54</anchor>
      <arglist>(Ptr addr, UInt size, Memory_AllocParams *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_dumpKnownContigBufsList</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gae2b6a9cc903ee184803d78581cd815ec</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>UInt32</type>
      <name>Memory_getBufferPhysicalAddress</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab8ec2b9417f2e0d7b2a6e82849809914</anchor>
      <arglist>(Ptr virtualAddress, Int sizeInBytes, Bool *isContiguous)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Memory_getHeapId</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga261148d59a10332670f91cf5c7462fc0</anchor>
      <arglist>(String name)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Memory_getNumHeaps</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga505cbdf622b39af1ce1816ef46f3afa2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>Memory_getBufferVirtualAddress</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga9bd3cbcc7d8eceee82736f85c88b31d9</anchor>
      <arglist>(UInt32 physicalAddress, Int sizeInBytes)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_registerContigBuf</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab52db9600a898de8c2be8c026bb1f64a</anchor>
      <arglist>(UInt32 virtualAddress, UInt32 sizeInBytes, UInt32 physicalAddress)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Memory_unregisterContigBuf</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>ga41460efdf79c34895257b9026acfcae8</anchor>
      <arglist>(UInt32 virtualAddress, UInt32 sizeInBytes)</arglist>
    </member>
    <member kind="variable">
      <type>Memory_AllocParams</type>
      <name>Memory_DEFAULTPARAMS</name>
      <anchorfile>group__ti__sdo__ce__osal___memory.html</anchorfile>
      <anchor>gab8c4500be062bef1624f2e073d23a838</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>SPHDEC</name>
    <title>SPHDEC Speech Decoder Interface</title>
    <filename>group___s_p_h_d_e_c.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_EOK</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga92a3df918ba687b8f146036550ba5e60</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_EFAIL</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaf6367169b44ba184320d80745278d238</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_ERUNTIME</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaee67760059368856c531da207d076882</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_ETIMEOUT</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga7b7a56b232d6dbb02dc27aa306e28a73</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC_FOREVER</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga2437e21028197990fb0c41d93d5b193b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_Status</type>
      <name>SPHDEC_Status</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga709a20a3cee84e1f8a5fb19075dba667</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHDEC_Handle</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga124f2ec0a80d2f16632370ffcbac67dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHDEC_Params</type>
      <name>SPHDEC_Params</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gaacff1229f5459ed1939251296cdb2633</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_InArgs</type>
      <name>SPHDEC_InArgs</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga63f28c45e727a836c94dfaec2c58bddc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_OutArgs</type>
      <name>SPHDEC_OutArgs</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga434544c79ca6cbd2496efa9d3efbe5ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_Cmd</type>
      <name>SPHDEC_Cmd</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga47cc6ecdf3b5ca74de1aadc31df27824</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC_DynamicParams</type>
      <name>SPHDEC_DynamicParams</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga4e4aac5fde7c50998c26d24640b1c88d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SPHDEC_Handle</type>
      <name>SPHDEC_create</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga232c0776f4982c2201dfcb6757c0ffcd</anchor>
      <arglist>(Engine_Handle e, String name, SPHDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC_process</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga004f2e4c06475e1be6cfe5116de80027</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC_control</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gae5f46950b9a073d239a65b1f1384f358</anchor>
      <arglist>(SPHDEC_Handle handle, SPHDEC_Cmd id, SPHDEC_DynamicParams *params, SPHDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHDEC_delete</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gad5ea3449c6b526c2e28abe0e3d5acc3b</anchor>
      <arglist>(SPHDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC_processAsync</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>gafa5ffa6904cf0b4b39568bd9759f4319</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC_processWait</name>
      <anchorfile>group___s_p_h_d_e_c.html</anchorfile>
      <anchor>ga577b44385b51c5096cd83fce8a7da2ba</anchor>
      <arglist>(SPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHDEC_InArgs *inArgs, SPHDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>SPHENC</name>
    <title>SPHENC Speech Encoder Interface</title>
    <filename>group___s_p_h_e_n_c.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_EOK</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gad3f08f36137b28184206e0d556682382</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_EFAIL</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga8d14cdd1fd63c45e7beba62c464d7ead</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_ERUNTIME</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaba65f74077e9f5fabae6290f7daffc08</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_ETIMEOUT</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga8f46879ca0532bef39f747a0db90811c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC_FOREVER</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gabdf81b5119e04965497bb3bc03a74d85</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_Status</type>
      <name>SPHENC_Status</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaecd0677714912ab15eef0caea71fe740</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHENC_Handle</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf23679c72ae5ebdff50a41a303986c6d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC_Params</type>
      <name>SPHENC_Params</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga2842b2174222faddcd192b21d3a8bbb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_InArgs</type>
      <name>SPHENC_InArgs</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga14cfec1b3a4ddd9ea05c948c7ab8a038</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_OutArgs</type>
      <name>SPHENC_OutArgs</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga4f72f1ded7ea0ff2436cb877348b621c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_Cmd</type>
      <name>SPHENC_Cmd</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga36c38dabf0e76a4997bea84c69f203a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC_DynamicParams</type>
      <name>SPHENC_DynamicParams</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga84d4de5a24fd34088f2a89cee9740aae</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>SPHENC_Handle</type>
      <name>SPHENC_create</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gacbd1973199095f0ed887f1046eeff06b</anchor>
      <arglist>(Engine_Handle e, String name, SPHENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC_process</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gaf6814914e4bc450d2caa945391fe25ca</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, SPHENC_InArgs *inArgs, SPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC_control</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga943e47b8ad0679f67a735c3179231e1a</anchor>
      <arglist>(SPHENC_Handle handle, SPHENC_Cmd id, SPHENC_DynamicParams *params, SPHENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHENC_delete</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gab01da27d7c58ef44be061fcbad6ae9b4</anchor>
      <arglist>(SPHENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC_processAsync</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>gae7ff164fe01fd37dbd74a63c0660279b</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC_processWait</name>
      <anchorfile>group___s_p_h_e_n_c.html</anchorfile>
      <anchor>ga64c4f46e8e591762837a6421d44f6e62</anchor>
      <arglist>(SPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_speech1_SPHDEC1</name>
    <title>Speech decoder codec interface</title>
    <filename>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga5232ca694305259bb78819295f4dd759</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga433c4f9b5a8936915dfd0e3e1fbd028e</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gafca3e9fd1bb4445bf78a54caa0096f3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gae61ef4c25010e9ed5889cc094a8ec1dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga85c427d8ec22820d6c4861fba4017954</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gae1ddcc35852dea0604c20c162e7518d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Params</type>
      <name>SPHDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga169fd7e3c58f327f6863d0ab0acee022</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_InArgs</type>
      <name>SPHDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf4691a7729e59c1bf020058e52761dc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_OutArgs</type>
      <name>SPHDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga55457f5b5dd1dbbd58136a3e8f0b8359</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Cmd</type>
      <name>SPHDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf6092fa1e6520963aac6677a9ef87f93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_DynamicParams</type>
      <name>SPHDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gacfb355f557a3fb8d02942d31b3c3631e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHDEC1_Status</type>
      <name>SPHDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga8e11c98ecdcb71083f14e20e3869d814</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gac8fe63b882294d4382f96e016a2fae74</anchor>
      <arglist>(SPHDEC1_Handle handle, SPHDEC1_Cmd id, SPHDEC1_DynamicParams *params, SPHDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>SPHDEC1_Handle</type>
      <name>SPHDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gabaaa5d041890db5856f581f7f14647b4</anchor>
      <arglist>(Engine_Handle e, String name, SPHDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaa3e46e8005792857153a2c7b24060301</anchor>
      <arglist>(SPHDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>gaf412f1ac7e1916740b152651dae3c470</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga5e7eea24460f6d509d73b83eb1d0ff10</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_d_e_c1.html</anchorfile>
      <anchor>ga61dff9f5240d85fd6bd83ada4077ecd9</anchor>
      <arglist>(SPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHDEC1_InArgs *inArgs, SPHDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_speech1_SPHENC1</name>
    <title>Speech 1.0 Encoder Codec Interface</title>
    <filename>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga420b4ae18c77a3edc291a526215f8f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gab106e36e90336b0d89b07fc52c399b2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga8e9fdde5fb595bb033b8316b6074a96b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaecddcea3a2fec9db91b1ce1f1a14938a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>SPHENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga056c1db84c81ddcf329fa12389c71bde</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>SPHENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaeaae5baa057d761fdf0aaa2c1a90371a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct ISPHENC1_Params</type>
      <name>SPHENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga94e8eddf1c310cc688a4acc5a23a55f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_InArgs</type>
      <name>SPHENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga1b8446b40a30318efd4b38a4f9cc1a2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_OutArgs</type>
      <name>SPHENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga37ba382f11470bbf0f418637310e7f7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_Cmd</type>
      <name>SPHENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaaacf82ccebcf2c82cf9080f33a5f2c46</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_Status</type>
      <name>SPHENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gac08769863d854dd6e2b3583d11a98af2</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ISPHENC1_DynamicParams</type>
      <name>SPHENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga1cf47ecb369d8aa3938fcc5036e5dfc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC1_control</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga9ef17b57fad768eee41970b68404e815</anchor>
      <arglist>(SPHENC1_Handle handle, SPHENC1_Cmd id, SPHENC1_DynamicParams *params, SPHENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>SPHENC1_Handle</type>
      <name>SPHENC1_create</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gabbaedd6e1b2a7e50c28eaf1d5b8ea076</anchor>
      <arglist>(Engine_Handle e, String name, SPHENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>SPHENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga42f0d42d062692e9749ba088111d7471</anchor>
      <arglist>(SPHENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>SPHENC1_process</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaea7cf777f9a3913d41dc2739080841b8</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>gaa5d8d68da3015bd180e68d0df90c7ec0</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>SPHENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__speech1___s_p_h_e_n_c1.html</anchorfile>
      <anchor>ga6b87cb1e8fed78dac4f6f3fb2c147d04</anchor>
      <arglist>(SPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_universal_UNIVERSAL</name>
    <title>Universal Algorithm Interface</title>
    <filename>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EOK</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gade20f2e69755596e8ba0c5492655ca8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga84a0b3a478663ef705e5892e98ec3841</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga2306b8d762ca96d1ffeaf28832dd64cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga56ab6f1bc8ebd19c9493ba51d106427f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIVERSAL_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga91688034ef01f08d844489c691a560fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>UNIVERSAL_Handle</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaf94abf3f8d7de2270695a31426498faa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IUNIVERSAL_Params</type>
      <name>UNIVERSAL_Params</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga867a8bdef066f152335d31a70e00337a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_InArgs</type>
      <name>UNIVERSAL_InArgs</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa6de5f43e559d284735ef9dfcc437cc9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_OutArgs</type>
      <name>UNIVERSAL_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gab00531077258820bd52e301929d7defc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_Cmd</type>
      <name>UNIVERSAL_Cmd</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gabfedfad116072edc4a8b7bb40cc9dfbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_Status</type>
      <name>UNIVERSAL_Status</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga7e6fc87fed2880856afd08057372ef0b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IUNIVERSAL_DynamicParams</type>
      <name>UNIVERSAL_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga81291e811b04126a73c48cf94869c533</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>UNIVERSAL_control</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaa5ead906fb8d7f70895bd1618b7b5bca</anchor>
      <arglist>(UNIVERSAL_Handle handle, UNIVERSAL_Cmd id, UNIVERSAL_DynamicParams *params, UNIVERSAL_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>UNIVERSAL_Handle</type>
      <name>UNIVERSAL_create</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>gaab5b0e7fa752fb4721dcfd72c77e4aae</anchor>
      <arglist>(Engine_Handle e, String name, UNIVERSAL_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>UNIVERSAL_delete</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga3f7b0d2a2d83ef78249d1896eec66d8f</anchor>
      <arglist>(UNIVERSAL_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>UNIVERSAL_process</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga63642cb1a9c0e2a9970a5cf8b78ee727</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, UNIVERSAL_InArgs *inArgs, UNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>UNIVERSAL_processAsync</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga352bfc67746de2ef1c210fff6d55ca0a</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>UNIVERSAL_processWait</name>
      <anchorfile>group__ti__sdo__ce__universal___u_n_i_v_e_r_s_a_l.html</anchorfile>
      <anchor>ga20dc67d51e8af763135d52fa601a5b00</anchor>
      <arglist>(UNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_utils_trace_TraceUtil</name>
    <title>Codec Engine Tracing Utility</title>
    <filename>group__ti__sdo__ce__utils__trace___trace_util.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>TRACEUTIL_SUCCESS</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga36e6d1770c3a6567a142d3d0d9926d3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TRACEUTIL_FAILURE</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga832483a3bbe3e98452265e8137f24a9b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>TraceUtil_start</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>ga0c1afd5c5805fd3c62dc81102f86ebd5</anchor>
      <arglist>(String engineName)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>TraceUtil_stop</name>
      <anchorfile>group__ti__sdo__ce__utils__trace___trace_util.html</anchorfile>
      <anchor>gae0fac5c1e0c29072fbdb81d944836bc0</anchor>
      <arglist>(Void)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_vidanalytics_VIDANALYTICS</name>
    <title>Video Analytics Algorithm Interface</title>
    <filename>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EOK</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga0e822caf655ba6614fb29af0ea2ab954</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga5e22f8669f1f8b477065fa1b5a596ab6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga95bfaa4802d03a8522ed71de50c396c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga3e8ab8c4c1dbc7612461bcd9998d7709</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDANALYTICS_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gafdc3d27c7684d46971f3c9e6c6fb9d03</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDANALYTICS_Handle</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga7b1cfa512e1fdbaf0dec0504f9030dfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDANALYTICS_Params</type>
      <name>VIDANALYTICS_Params</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gade82de22bf14e7c26228de02a97c8505</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_InArgs</type>
      <name>VIDANALYTICS_InArgs</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga66d090369dd7cd22546bc58f16a597b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_OutArgs</type>
      <name>VIDANALYTICS_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gac540b9a8699431477786da498b90943d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_Cmd</type>
      <name>VIDANALYTICS_Cmd</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaaa6db913ea6f620f04341a7cc163fd1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_Status</type>
      <name>VIDANALYTICS_Status</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>gaa36b9ad7b1697fa8297383ef25c16f57</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDANALYTICS_DynamicParams</type>
      <name>VIDANALYTICS_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga732f41d71282aa4ca090eb576f53308c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDANALYTICS_control</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga7647b22d5c00bb0eef791f8835b3f3d8</anchor>
      <arglist>(VIDANALYTICS_Handle handle, VIDANALYTICS_Cmd id, VIDANALYTICS_DynamicParams *params, VIDANALYTICS_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDANALYTICS_Handle</type>
      <name>VIDANALYTICS_create</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga475a5abb26a90250ff1e08b7dbbbbf63</anchor>
      <arglist>(Engine_Handle e, String name, VIDANALYTICS_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDANALYTICS_delete</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga846c8e8530f77bf98350357080990a78</anchor>
      <arglist>(VIDANALYTICS_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDANALYTICS_process</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga98b6938cbd2df4278724f153801ac304</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, VIDANALYTICS_InArgs *inArgs, VIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDANALYTICS_processAsync</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga992c1e5deadb65ddcd8c9dfb50e97678</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDANALYTICS_processWait</name>
      <anchorfile>group__ti__sdo__ce__vidanalytics___v_i_d_a_n_a_l_y_t_i_c_s.html</anchorfile>
      <anchor>ga738e654701f883c9a2512a009297ad1d</anchor>
      <arglist>(VIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>VIDDEC</name>
    <title>VIDDEC Video Decoder Interface</title>
    <filename>group___v_i_d_d_e_c.html</filename>
    <class kind="struct">IVIDDEC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_EOK</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gabe8baab72eab6424a41a0a334494a612</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_EFAIL</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaa249b3a8fd01220a42f36b7707241a09</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_ERUNTIME</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga146bda97c8799172061993fcefc8fe13</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_ETIMEOUT</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga7e936b48259312164afce8fec9a6ce8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC_FOREVER</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga06f0c028245349a1a7d9b1e90f8cbda8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_Status</type>
      <name>VIDDEC_Status</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf616c0e56d16935941dab2be391de913</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC_Handle</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga92af2feff2dd294d434283085ddead93</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC_Params</type>
      <name>VIDDEC_Params</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaabd72bd755a04c88491205a3f9fe839c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_InArgs</type>
      <name>VIDDEC_InArgs</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga55e28d443fb4ee87d6bc5c9b4d6e063e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_OutArgs</type>
      <name>VIDDEC_OutArgs</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga0f35489e308e32dadf4a37b102eb9541</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_Cmd</type>
      <name>VIDDEC_Cmd</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga4c04ae2e12da9b8cf009476ef20e154c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC_DynamicParams</type>
      <name>VIDDEC_DynamicParams</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaf9afbae3ad253f919a948aafd30ac07d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC_Handle</type>
      <name>VIDDEC_create</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga8ed0216fe02a3ba35a0672fd7df00079</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC_process</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gaab4faa31ebf26cf9c182d48417ea205c</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC_control</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga3a8e01918dff1f556a18968ce96611c8</anchor>
      <arglist>(VIDDEC_Handle handle, VIDDEC_Cmd id, VIDDEC_DynamicParams *params, VIDDEC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC_delete</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gadf312f577bb4f0040eceede27de93b37</anchor>
      <arglist>(VIDDEC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC_processAsync</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>ga8f6138c30e0856574e0829fe1807bd59</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC_processWait</name>
      <anchorfile>group___v_i_d_d_e_c.html</anchorfile>
      <anchor>gac8dcb55012c5e2360f025489b3457fb1</anchor>
      <arglist>(VIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC_InArgs *inArgs, VIDDEC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>VIDENC</name>
    <title>VIDENC Video Encoder Interface</title>
    <filename>group___v_i_d_e_n_c.html</filename>
    <class kind="struct">IVIDENC_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_EOK</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga8776fd0a4ddd63edd36f3979dfddb9a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_EFAIL</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gaa6c3de08b2a584976be0ffde2c4b81b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_ERUNTIME</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gac411d1a2c3e5c67a5718287d317a5483</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_ETIMEOUT</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga6eaed37ed3338e8de39c6a258362dc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC_FOREVER</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga4807e4e1fbf632d1c9e22772d15c8b74</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_Status</type>
      <name>VIDENC_Status</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga15fc4a0dd5b06f14b8509091a1107283</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDENC_Handle</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga60925466f910025443b791cd7894cc56</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC_Params</type>
      <name>VIDENC_Params</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga376be7b4739d843736f3056b46cfb35c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_InArgs</type>
      <name>VIDENC_InArgs</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga21aae5070ed29e590579ac1c84f56b20</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_OutArgs</type>
      <name>VIDENC_OutArgs</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga50ec5c9f9cdc4ba3db8f8872ed2ef523</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_Cmd</type>
      <name>VIDENC_Cmd</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga926b28b5c17d2e610c45aa71d0628199</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC_DynamicParams</type>
      <name>VIDENC_DynamicParams</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>gae88a985907e854439eae82add1c74aa5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDENC_Handle</type>
      <name>VIDENC_create</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga86a8acd4d73fa48db484000ff2960485</anchor>
      <arglist>(Engine_Handle e, String name, VIDENC_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC_process</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga9dc7650ae11474f7b80209ec6268885d</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDENC_InArgs *inArgs, VIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC_control</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga9e61bdaa46802daa9847a46a7c04df4e</anchor>
      <arglist>(VIDENC_Handle handle, VIDENC_Cmd id, VIDENC_DynamicParams *params, VIDENC_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDENC_delete</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga79a7f95f66d5dac756f8c13db7bc74ff</anchor>
      <arglist>(VIDENC_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC_processAsync</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga5c572b93e4213eb2419af7ee5fd51eda</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC_processWait</name>
      <anchorfile>group___v_i_d_e_n_c.html</anchorfile>
      <anchor>ga59e66a5eab3c01669bf5067310e44b28</anchor>
      <arglist>(VIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_video1_VIDDEC1</name>
    <title>Video 1.0 decoder codec interface</title>
    <filename>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</filename>
    <class kind="struct">IVIDDEC1_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gabea208cf8275b6267f338f3e58bd2eda</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae412e487e8adee75b0b57d17740af43b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga9357b6663fdd9da55639389904a9c0f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga772eaf3172b528c7c6aa002a400cb21c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gae1f23780dcc21fc13b2e5c7e53cb1455</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_Status</type>
      <name>VIDDEC1_Status</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga74bbcba5eaa9e453394132ca532162ba</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga1f1ddc163e5211b25047e7d848025620</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC1_Params</type>
      <name>VIDDEC1_Params</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga872f6fb297fe7326cbceb54396e8fce6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_InArgs</type>
      <name>VIDDEC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga74ac24e03859ca89e1824e73e455a3b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_OutArgs</type>
      <name>VIDDEC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga01cdae55d171241b1f214045b67ebc92</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_Cmd</type>
      <name>VIDDEC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gaa483cca0045f226d99458f15a0fb6cf1</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC1_DynamicParams</type>
      <name>VIDDEC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga10255d56ff2813f7c337edc25c11ee36</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC1_Handle</type>
      <name>VIDDEC1_create</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga96bf80485afe49b889761b17fbf9eef5</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC1_process</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga30436231ebf7f58455177dcd1fbabe12</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC1_control</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga7b8aeb30459218bdff63d38eaac5b2ec</anchor>
      <arglist>(VIDDEC1_Handle handle, VIDDEC1_Cmd id, VIDDEC1_DynamicParams *params, VIDDEC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC1_delete</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga9928301c0880243d149cbc85871f216d</anchor>
      <arglist>(VIDDEC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>ga1ed176130043de491e631255700622a5</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_d_e_c1.html</anchorfile>
      <anchor>gabf7ba6ea9536c583979edb1082baf0db</anchor>
      <arglist>(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_video1_VIDENC1</name>
    <title>Video encoder codec interface</title>
    <filename>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EOK</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf27bfd83fb1e65f85f6985a1573bae40</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga42effe0110f0c61408fe59f4b1ed7555</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gac6ba8504c98c6dd6a2475d2f3e893547</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gad5790cadb1681ae5989a14da65068519</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDENC1_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga5a8494b6501ae82147533f482ad31869</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_Status</type>
      <name>VIDENC1_Status</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga8977b714f595bca81f381cb44f079b0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDENC1_Handle</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga422c0ee1b56306b13c598d0d9718db50</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDENC1_Params</type>
      <name>VIDENC1_Params</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga3b71b156c370cb7d2c260421c1a60d76</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_InArgs</type>
      <name>VIDENC1_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gad088c2553eddd215647f4670e7c6f24d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_OutArgs</type>
      <name>VIDENC1_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga9939b7fa369bd00d82e727fb0bc35aad</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_Cmd</type>
      <name>VIDENC1_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga2cd4de792e4191e0fad7adccbb2e337c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDENC1_DynamicParams</type>
      <name>VIDENC1_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga604ea63d97916c49027e7c172964e00c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDENC1_Handle</type>
      <name>VIDENC1_create</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga5100bd55908105eb918430a13b4c964d</anchor>
      <arglist>(Engine_Handle e, String name, VIDENC1_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC1_process</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga84cc9c14cb3fb8d5104864e0bb91c430</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, VIDENC1_InArgs *inArgs, VIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDENC1_control</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gaf24ed59a2cf8589af04868d2c3a3ea09</anchor>
      <arglist>(VIDENC1_Handle handle, VIDENC1_Cmd id, VIDENC1_DynamicParams *params, VIDENC1_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDENC1_delete</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga203fcb7c17c37398f03dd6df2b08ae05</anchor>
      <arglist>(VIDENC1_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC1_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>ga4d59054512de34e9a765874db7ca0587</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDENC1_processWait</name>
      <anchorfile>group__ti__sdo__ce__video1___v_i_d_e_n_c1.html</anchorfile>
      <anchor>gabeb4b67c5c85568d00bbbf982e69a315</anchor>
      <arglist>(VIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_video2_split_VIDDEC2</name>
    <title>Split video decoder interface</title>
    <filename>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2BACK_CodecClassConfig</class>
    <member kind="typedef">
      <type>IVIDDEC2FRONT_Status</type>
      <name>VIDDEC2FRONT_Status</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga891a3eae7577a2cfe055450915c9d91a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga6f2df412d30edb0a9eef16a5c1e8a811</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac2b371eda3c2797d4baaa5562e06be26</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2FRONT_OutArgs</type>
      <name>VIDDEC2FRONT_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga9269db4573b24702bbc06d98cb8f9028</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2BACK_Handle</type>
      <name>VIDDEC2BACK_create</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga20a1d1dc28b380ee28abbe218089540e</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2BACK_process</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaf43b4174649994910eb79da042d8323c</anchor>
      <arglist>(VIDDEC2BACK_Handle handle, XDM_Context *context, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2BACK_control</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7cfc70c5b7dbe2682a6bcae620a10710</anchor>
      <arglist>(VIDDEC2BACK_Handle handle, XDM_Context *context, VIDDEC2_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2BACK_delete</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga872721952f0336f9163b5fba807e12f3</anchor>
      <arglist>(VIDDEC2BACK_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2FRONT_Handle</type>
      <name>VIDDEC2FRONT_create</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga1826ac5b4bcaf171b160252ed31524c6</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2FRONT_process</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa394094a6be5bd28a5f72291a95d3f1b</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle, VIDDEC2_InArgs *inArgs, XDM_Context *context, VIDDEC2FRONT_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2FRONT_control</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga457bfc26428e0dc7196b8ed022ad1438</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle, VIDDEC2_Cmd id, VIDDEC2_DynamicParams *params, XDM_Context *context, VIDDEC2FRONT_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2FRONT_delete</name>
      <anchorfile>group__ti__sdo__ce__video2__split___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga48d6c3eaa755fb821d466879359c8cc2</anchor>
      <arglist>(VIDDEC2FRONT_Handle handle)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_video2_VIDDEC2</name>
    <title>Video decoder codec interface</title>
    <filename>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2_CodecClassConfig</class>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EOK</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga17a280c6bc345a31e94a2ccfbad75e30</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gabb22d106ff08094e22232b73b2c13151</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga6684057aee13ca029c22820491c816c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gadde8d402919cb93efeaad88207db5c01</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDDEC2_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8db99cb190a3ee911cbbf25b22ac0751</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDDEC2_Handle</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga825bedfe8430826abe48cf19cde5bcc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Params</type>
      <name>VIDDEC2_Params</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga574bccbb2b8cdd6cef48c4509cee4a04</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_InArgs</type>
      <name>VIDDEC2_InArgs</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga69f197d86e2e9db761ad6ae75569771e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_OutArgs</type>
      <name>VIDDEC2_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga61407f29da10c8e036ba3d847d2d4ec8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Cmd</type>
      <name>VIDDEC2_Cmd</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga881b58af927563dfc3e920aaab508e8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_DynamicParams</type>
      <name>VIDDEC2_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaf527166a656bd4278329ae28ddf96729</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDDEC2_Status</type>
      <name>VIDDEC2_Status</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga82b958e99f98898c9a769f501e112979</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2_control</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac56066dfb51357ff6a7e85c39c6923d3</anchor>
      <arglist>(VIDDEC2_Handle handle, VIDDEC2_Cmd id, VIDDEC2_DynamicParams *params, VIDDEC2_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDDEC2_Handle</type>
      <name>VIDDEC2_create</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga18eacdfbf4cedbfa125d6e3aabbf93be</anchor>
      <arglist>(Engine_Handle e, String name, VIDDEC2_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDDEC2_delete</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga7a16583250a5169335bd4ea6a39f5751</anchor>
      <arglist>(VIDDEC2_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDDEC2_process</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaa9fdbcf0841f7e8283764b3b75d61313</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC2_processAsync</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gac8f023338811207859cb38a6ac46e5f6</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDDEC2_processWait</name>
      <anchorfile>group__ti__sdo__ce__video2___v_i_d_d_e_c2.html</anchorfile>
      <anchor>gad3aef2ba0e5e3682467a1caea51a7483</anchor>
      <arglist>(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_vidtranscode_VIDTRANSCODE</name>
    <title>Video Transcoder Codec Interface</title>
    <filename>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EOK</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga4947ac42f9f0f2f7c1c9a87a210c739b</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EFAIL</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gac61f5cae4837ad8b98b01184d777d812</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_EUNSUPPORTED</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae522ab0ff96ec987ac91267a241fbc6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga805de75c31022068be40a35d71db5be0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VIDTRANSCODE_FOREVER</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaa00159f19b62efc8b3f587c0a9685026</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>VISA_Handle</type>
      <name>VIDTRANSCODE_Handle</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaaf087646fa33289c25338a3732a113cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDTRANSCODE_Params</type>
      <name>VIDTRANSCODE_Params</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga3a8256b227d1b242ce8d440bb4f77e44</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_InArgs</type>
      <name>VIDTRANSCODE_InArgs</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae6d29cb086517d71502a98e57813d120</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_OutArgs</type>
      <name>VIDTRANSCODE_OutArgs</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gae1c69202d86064a5921ef4278b694440</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_Cmd</type>
      <name>VIDTRANSCODE_Cmd</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga51fc2c5f7247b0568219f4d59b55dd5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_Status</type>
      <name>VIDTRANSCODE_Status</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9fc37e582bba0df08dc414a4deedf225</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>IVIDTRANSCODE_DynamicParams</type>
      <name>VIDTRANSCODE_DynamicParams</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga14984cc5d63cfac48889c0990a8d3fc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDTRANSCODE_control</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga903722dd7468db37879e5a2552ed8464</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, VIDTRANSCODE_Cmd id, VIDTRANSCODE_DynamicParams *params, VIDTRANSCODE_Status *status)</arglist>
    </member>
    <member kind="function">
      <type>VIDTRANSCODE_Handle</type>
      <name>VIDTRANSCODE_create</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9d960312911326bcfc63986ffbfb9a98</anchor>
      <arglist>(Engine_Handle e, String name, VIDTRANSCODE_Params *params)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VIDTRANSCODE_delete</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga7054b57f8dcc78871d26dc8f2802f7fe</anchor>
      <arglist>(VIDTRANSCODE_Handle handle)</arglist>
    </member>
    <member kind="function">
      <type>Int32</type>
      <name>VIDTRANSCODE_process</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga9e1e02c13d93a607fa824c84813f37c3</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, VIDTRANSCODE_InArgs *inArgs, VIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDTRANSCODE_processAsync</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>gaa1bc43c4f87a40841583ad98eb9ff182</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="function">
      <type>XDAS_Int32</type>
      <name>VIDTRANSCODE_processWait</name>
      <anchorfile>group__ti__sdo__ce__vidtranscode___v_i_d_t_r_a_n_s_c_o_d_e.html</anchorfile>
      <anchor>ga640c33a61a07c41ea4deff528b4f3968</anchor>
      <arglist>(VIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs, UInt timeout)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_VISA_GEN</name>
    <title>VISA</title>
    <filename>group__ti__sdo__ce___v_i_s_a___g_e_n.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>VISA_EOK</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga2edbcef572bbd8d30c6bb349db86fe5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_ERUNTIME</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaad5846943a2f5bc0fab9ce0cfb0e11aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_EFAIL</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaa1444d9197068455a077da8d42462b16</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_ETIMEOUT</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga982385711ed018e821510af2ae34decf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>VISA_FOREVER</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga4357bfb7aae9bdb6f49a67df470249a5</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int</type>
      <name>VISA_Status</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gaaf6296a78da6640be7ec774731d9b100</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_getAlgMemRecs</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga2c45fde612a6f225bb6498120d7d87e1</anchor>
      <arglist>(VISA_Handle visa, IALG_MemRec *memTab, Int size, Int *numRecs)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_getAlgNumRecs</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gac6783c6ff2b4f8338f1c82249bdc5fe3</anchor>
      <arglist>(VISA_Handle visa, Int *numRecs)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getCodecClassConfig</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gabf9abcbb0df0613151195aba068a30f8</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>UInt</type>
      <name>VISA_getMaxMsgSize</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>ga17cce3a55dc66766af54966406dcf0e0</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Bool</type>
      <name>VISA_isLocal</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___g_e_n.html</anchorfile>
      <anchor>gad9a95e8263867eea049235d2ffc61668</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_VISA_STUB</name>
    <title>CE Stub SPI</title>
    <filename>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</filename>
    <class kind="struct">VISA_MsgHeader</class>
    <member kind="function">
      <type>VISA_Msg</type>
      <name>VISA_allocMsg</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gabf5c5af35ea69f1ef725b5bfd6faa912</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_call</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga1ef4ab81afea6e041c7d36f88cc180a8</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_callAsync</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gad92dedea2968a5ef4aa8b12675c0af44</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Status</type>
      <name>VISA_wait</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga6087effc1133a0ad99ae68c3cc1233cf</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg *msg, UInt timeout)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_freeMsg</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga36209656e4a94e17c8edded097ab95cc</anchor>
      <arglist>(VISA_Handle visa, VISA_Msg msg)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_getContext</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>gaf267d181beb7da616c423a934ea9a92c</anchor>
      <arglist>(VISA_Handle visa, UInt32 *pContext)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_setContext</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___s_t_u_b.html</anchorfile>
      <anchor>ga81d34e425ad23de06e05e7996dbfde94</anchor>
      <arglist>(VISA_Handle visa, UInt32 context)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_VISA_API</name>
    <title>CE interface SPI</title>
    <filename>group__ti__sdo__ce___v_i_s_a___a_p_i.html</filename>
    <member kind="function">
      <type>VISA_Handle</type>
      <name>VISA_create</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga0763f9de306c1e8c3ed68ef849234b94</anchor>
      <arglist>(Engine_Handle engine, String name, IALG_Params *params, size_t msgSize, String type)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_delete</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga3bec94bcc2149b76ec4f51bd968744e5</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>VISA_Handle</type>
      <name>VISA_create2</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gaca27816a9a296b172f819f5a074fb812</anchor>
      <arglist>(Engine_Handle engine, String name, IALG_Params *params, Int paramsSize, size_t msgSize, String type)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_enter</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga8dbcaeadf2a560877db77c61cc67342f</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>VISA_exit</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga2ea2abaca0018497421126bdf63136be</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getAlgHandle</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gae8bf0905dd129158701623b858e83e92</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>Ptr</type>
      <name>VISA_getAlgorithmHandle</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>gabe11eada20b930e4eb019c3ca75a1e36</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
    <member kind="function">
      <type>IALG_Fxns *</type>
      <name>VISA_getAlgFxns</name>
      <anchorfile>group__ti__sdo__ce___v_i_s_a___a_p_i.html</anchorfile>
      <anchor>ga5c8a043fd48d1c00f22d213e5062e614</anchor>
      <arglist>(VISA_Handle visa)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_IVIDEO</name>
    <title>XDM Video Interface</title>
    <filename>group__ti__xdais__dm___i_v_i_d_e_o.html</filename>
    <class kind="struct">IVIDEO_BufDesc</class>
    <class kind="struct">IVIDEO1_BufDescIn</class>
    <class kind="struct">IVIDEO1_BufDesc</class>
    <member kind="define">
      <type>#define</type>
      <name>IVIDEO_MAX_YUV_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6f88ee11da1a2397e9ac263ce3cdd537</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameSkip</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga6533d232a1c479dd185945e9c10c2665</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NO_SKIP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a8089c337b034434f8d53d279022272f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_P</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a767894b6dfb8639c2298f2d31e5fee51</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_B</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a04cadb8d98980be81a2a8a3fdc0372fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_I</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a551353a345ce3929adcff79aa741724b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a1b9f609f763ae7d8b36262986bcf54a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad111bef6602a59d8998ba5b4adbce87b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_PB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a2e82d4e64d50c7fae14a1ef6720d3588</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IPB</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665ad9ffc660a588536746fbdb3d8b5b4f33</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_IDR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a98a74bb46bd05f43c4db0ae8f8f66eb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIP_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga6533d232a1c479dd185945e9c10c2665a0f0844d71eeb68ce22bc9d9f840d93f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_FrameType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7ad672ade5d380f42e0cfcfb2b38b6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfab4b11cfbf563ce054e55fa482fb67f79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac2b378280d95551841dddec15fad1d43</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad788ad7b0f7a8517de35c5cd0aefc28d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa7dd078d4f4f309da2e73494ddd01f2b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfad7a86650a7f248f11133e52da2cb3e36</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_II_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3be138a2faa58c0d85e2ae533526af79</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa40d74846bed523f78efbd61e42736dea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_IB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9cc0602312932db087a8e89b807c59a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa394be4bc1774efef87892bcb6387d4d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa9ae131687a2c620b50be3cb9bdf9ef69</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa3eb025061d65605fa2613a1219203662</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BI_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa99b48bce066d122f86f67d281709c970</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BP_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf6d75d28ac6582ed372ca9dcffd7a31e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_BB_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaa8dad288ba397bafe98f9d3dcda06efd</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_I_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac0c3748111b37e34c2652e311b367f18</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_P_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa068cd4d6a1d797d1b3eba96255c64b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_B_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfac34147d75fecab15f7692ff0be138df6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MBAFF_IDR_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfaf9c5b520fe2612d88725de4bc1224d28</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAMETYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7ad672ade5d380f42e0cfcfb2b38b6dfa05a31e040d22bea216e10f2ce8cd6472</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_ContentType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gac397e10110dd59e8266cf5831c68f44f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_NA</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa61cc12c39b88ba4c10d51a9d9393405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa6b7ae345e50ccd4c5589efd85e18194e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PROGRESSIVE_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa36a57cca2ad3435c423515e78dd7d1ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa53e2513e3f2b155abb3bb707ff2fbd04</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_FRAME</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa399d126875549ace3806efddcfc45ce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_TOPFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa74d16186e87100648b97eae32e72d90c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_INTERLACED_BOTTOMFIELD</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa980c869708ff1245fd7f1859515da631</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_CONTENTTYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ggac397e10110dd59e8266cf5831c68f44fa35c626f7476288db897680bc43d92243</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_RateControlPreset</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga33dcd88e11f7c1a614c37729e6b99592</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_LOW_DELAY</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592aee9478fdaa09a124e84a5f52373213f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_STORAGE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ad38ab0817089a19a753e2ca6b6e5d165</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_TWOPASS</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abf4ba1f0aff97d13bf49af0d574ad040</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NONE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592ae222e2b721a93726945d9b563631fda0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592a8e5fffe1c7bb0d34fd55b8820cfdb7e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_RATECONTROLPRESET_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga33dcd88e11f7c1a614c37729e6b99592abafd796f46fc51340a58dadf2f725e25</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_SkipMode</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga911b2a9c63a7a8c16b86ae2b43acb609</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ENCODED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a899d064f2315fc727725330cec39a441</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_SKIPPED</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609a728d909773039ecb6c8481ce587ff948</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_SKIPMODE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga911b2a9c63a7a8c16b86ae2b43acb609ac81722aae2d59cad8cb864dc68c81d23</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_OutputFrameStatus</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga7d713a3e9b5adacb039de4419d5527d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4acb9c873639468d10824089bf2c196884</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_NOTAVAILABLE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a3884312affd02cbb477b0bcf9ffa4a8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_FRAME_ERROR</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4ae22471e0df0ebdbc17ad840deec9ba24</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_OUTPUTFRAMESTATUS_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga7d713a3e9b5adacb039de4419d5527d4a4bcc02f48972d600ec61e933133b4587</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_PictureType</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga90dd6a0a4863fcc6d3d523eda8a78ed2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_NA_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aed1dec6b10bca143d42b83d26218d26e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_I_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a85a519797900b0bbbc5007c14e6bab37</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_P_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a70166338c9fab34bb0fc6534a0890ea3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_B_PICTURE</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2aa8b180d5b01bb100e326d261684ba7f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_PICTURE_TYPE_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga90dd6a0a4863fcc6d3d523eda8a78ed2a5373e837eb3564b15e0a0203ecdb503f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>IVIDEO_Format</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>ga4aeb19b8e5cc42c49fc8820fc4e1b4aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG1</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa6b8d27c8e2c977e98780b30be68b4553</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa1d3f020030f6624621f546640cd97195</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa77ef7b91a48b372bb8fd6104ba4c53d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG2HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa8cd7c6245521d4003ae12244eb8616e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa58cce125a57189f5ad23250b0ea41dce</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_MPEG4ASP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa35e77ca8ec953280e5615eb9e799211b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264BP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaab62f85b5ad0f3716733800202de13725</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa65745c33e161b9e725dd1093d6afb535</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_H264HP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa204e56351a5162ac38b3abfe5456ab87</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1SP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaabb227ae9ca9aea83e804a2afc9137e67</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1MP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaa673d0eb07f8c957878812eebe0074b8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IVIDEO_VC1AP</name>
      <anchorfile>group__ti__xdais__dm___i_v_i_d_e_o.html</anchorfile>
      <anchor>gga4aeb19b8e5cc42c49fc8820fc4e1b4aaadf58ee1effdc2c92756355575b471123</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_split_IVIDDEC2</name>
    <title>XDM IVIDDEC2-based Video Decoder Split Interface</title>
    <filename>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</filename>
    <class kind="struct">IVIDDEC2FRONT_Obj</class>
    <class kind="struct">IVIDDEC2BACK_Obj</class>
    <class kind="struct">IVIDDEC2FRONT_Status</class>
    <class kind="struct">IVIDDEC2FRONT_OutArgs</class>
    <class kind="struct">IVIDDEC2FRONT_Fxns</class>
    <class kind="struct">IVIDDEC2BACK_Fxns</class>
    <member kind="typedef">
      <type>struct IVIDDEC2FRONT_Obj *</type>
      <name>IVIDDEC2FRONT_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>gaaa273ba82e5f6d894000c4031d905776</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct IVIDDEC2BACK_Obj *</type>
      <name>IVIDDEC2BACK_Handle</name>
      <anchorfile>group__ti__xdais__dm__split___i_v_i_d_d_e_c2.html</anchorfile>
      <anchor>ga8aedc496483d9ad90fb544045934648d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_dm_XDM</name>
    <title>Shared XDM Definitions</title>
    <filename>group__ti__xdais__dm___x_d_m.html</filename>
    <class kind="struct">XDM_BufDesc</class>
    <class kind="struct">XDM_SingleBufDesc</class>
    <class kind="struct">XDM1_SingleBufDesc</class>
    <class kind="struct">XDM1_BufDesc</class>
    <class kind="struct">XDM_AlgBufInfo</class>
    <class kind="struct">XDM_Date</class>
    <class kind="struct">XDM_Point</class>
    <class kind="struct">XDM_Rect</class>
    <class kind="struct">XDM_ContextInfo</class>
    <class kind="struct">XDM_Context</class>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EOK</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga1cf6109227485a043be42d0761ed55b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EFAIL</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac896f031d1997aae6f959aff6c6d8b54</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_EUNSUPPORTED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac502a6ae2494d2c4151e2a3be22c96e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ERUNTIME</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa1a1d3d9c0c8807cbe465633d76580e4</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_IO_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacb0db1cbd37d45e39368c0dff87d7cef</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga3446a438727f673f58cacd76947536d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaa0360329abe8080abb150c24255fa3a7</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaedd624063fce29cfed9193ad4d46765c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CLEARACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacaf2e719f6570fb074df83697f9665d1</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gac4c3d846ed83c34a06fd6e8fcb49b4b2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaef2577b3a010843a01d85a6e2bbf5487</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMENUMBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6eae9fc7c3a5e8aa08d3d23d870b583</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_CUSTOMCMDBASE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga43093f03f01c2e4eed7f131795af84fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf46ec0675f5fae35aaf29392aebbe3d3</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gae1b52e8b2c8c062dd460f8a9bc737b77</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gacc71215dc73ce6f3184f78be7c49ac09</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4979bf4ca24fca5d9386896f9c319084</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga180c829e45389f064af38a3e58278baa</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7714cc631b009ef2c574218006af0ebb</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_ISAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga24d74d9ea55947f6bf2bc90a532bc32c</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETFATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab0d647a23e89f0a11fb47493746bc254</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad4b20720fe6a8d9eb46259206635c6ab</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETUNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaf6a007a552f8849694b6c785531c9413</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad5b5a780c1df72c1a99f28c1e32531be</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETCORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7cab971a59a1057febe113621ac68c1b</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETINSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga89f38db60d38746c435f8d9f2398bef2</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_SETAPPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga22e33071e27e1f3d1624229986c79331</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDM_MAX_CONTEXT_BUFFERS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gaed28c56a4d5a516897357c2fc647ac9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_AccessMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gad852bdfa0303e77939811768b8e905ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_READ</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905abadc6547990f2ba9c7a4bacdf3ad4f405a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ACCESSMODE_WRITE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggad852bdfa0303e77939811768b8e905ababd16ad36f147cf0e691a13590314a06c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_CmdId</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga4d2482d53629e138b96af2e3fe702477</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETSTATUS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a901d6409e5496dbc7720d0e952fb1b15</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETPARAMS</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477ab358f49d17f79c00b1ba5c2c645eb025</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RESET</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a2bf3cef324828ab92cd6cedead4c725e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_SETDEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a1b6cda1632a452aa55dbba763b53d746</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FLUSH</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477acd0e4d7005b1df978b26f97bccf6df8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETBUFINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477aac803fc3c3144acc395e3b9b79025653</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETVERSION</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a6531ed0c0766017f6caa01207d3ad4c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GETCONTEXTINFO</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga4d2482d53629e138b96af2e3fe702477a7aa270e718dce742ef06b8d67be98055</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ErrorBit</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga993de0b923e61c59a996fc2be4783131</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARAMSCHANGE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a13eb40f973b1bc18df8263030d4a1be9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_APPLIEDCONCEALMENT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a143f0496fb2db7191d7ddbe9d9fb58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_INSUFFICIENTDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131aeb5f7b677fb1d35ce8c9e4af0e1c5c2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDDATA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3df4766dd604b28652b8830f051a7e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CORRUPTEDHEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131afab843e2d029e916fc36e7550489dba9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDINPUT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a7c4145225db773b55c02bcc61be59756</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_UNSUPPORTEDPARAM</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a3440c95956b613e002620a71c77a5980</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_FATALERROR</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga993de0b923e61c59a996fc2be4783131a8ebb569b30333486afaf576c366118e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DataFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga5b4416e5582cae4428a1f4695d6e5ac5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BYTE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5aa24eeba74896e53a4bb8874560e4f67d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a286615517f0d85bbad01a61ca1b8355b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a87cbb4b143f78faf0f5c67d45cd5a39a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_LE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a111d1dcf71c52bd2c9886373a5d98e1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_16</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a3dac2b3e9961a294c89ffac5ceedb509</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_32</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a43e43097fd1b63ac44247df52fe88da4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_BE_64</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga5b4416e5582cae4428a1f4695d6e5ac5a82ae547ec4f91e70c0dec56dd35c624d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncodingPreset</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7b522f4337b661bbf9fb649eb95b4e1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1ca72b9373f4561db5fc6b0a2904b4a40e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_QUALITY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1cabef4cff45b90786a8583b027530bb927</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_HIGH_SPEED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caf553ad9672b1ee9a7b91d746980dc58a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_USER_DEFINED</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7b522f4337b661bbf9fb649eb95b4e1caba3ac3c750ac0125c9f1aac6f8586b5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_DecMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga0e19341fdb7c698eb849896edaa33aff</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_DECODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa8c540496685639e09e8c1ef895565595</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_PARSE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga0e19341fdb7c698eb849896edaa33affa20a585ea8dd3b153c5203499b54d862c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_EncMode</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ga7e9132a2379c6ac0ee9c9e925b932461</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ENCODE_AU</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a5822b75801cd51f3a5f3478d59c8bee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GENERATE_HEADER</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gga7e9132a2379c6ac0ee9c9e925b932461a98969caa951cc0b210bacdd2a1932abc</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>XDM_ChromaFormat</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>gab99980ebd17efe73aa5708b5f43107f4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMA_NA</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aef81026a1d1783d9628c19f5c8a78dac</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a891298e42c828a4c56b2d20d8be7cca8</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9457339c11ffa04dca5f900e82a2346d</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422IBE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a638d86b7f38f9404348b38fa459bdee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_422ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a9560c4d0b7a2ddb6aba01ca66e41e5ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a31ade59366a5116a6d74a4fe012021f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_411P</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6c2c3aac53d2a8da477f487d788bcb29</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_GRAY</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a45edf9e2ce7ab4045dfcdde062b4e423</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a0491c6350cc8c9127610c2a6c31f3ee4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_420SP</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4acd45176e14ea9e5b53fc52ec88bddd9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_ARGB8888</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a5979b38c73531a7bf71c12412232be5c</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB555</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aa1ae21243fd451d6a8f75bd274a77934</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_RGB565</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4a6b8863fc2937c932888f3df04ff1bcc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_YUV_444ILE</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4aaf1809f33e309f991f8c47b6af55399a</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>XDM_CHROMAFORMAT_DEFAULT</name>
      <anchorfile>group__ti__xdais__dm___x_d_m.html</anchorfile>
      <anchor>ggab99980ebd17efe73aa5708b5f43107f4af01b00784f3926f7accfd6f0a8360a7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_xdais_XDAS</name>
    <title>XDAIS Types and Constants</title>
    <filename>group__ti__xdais___x_d_a_s.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_TRUE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga0a1e9fe6b661ca6eafe982fe2b0787bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>XDAS_FALSE</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga5cd894ca3ba5c100f7f863dae8587293</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Void</type>
      <name>XDAS_Void</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga125aad4180e7ca9a3ddaba59c9217513</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_Bool</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac8ce48f3d618a6f0a37b4e55f978b825</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int8</type>
      <name>XDAS_Int8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa0b0c4cc1bf0d8fa0d9b15de0e9204cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint8</type>
      <name>XDAS_UInt8</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gac9308edb855a360c27a47aaa6f3b39a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int16</type>
      <name>XDAS_Int16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga8189aa7a8636f505d6a35e5744ac6392</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint16</type>
      <name>XDAS_UInt16</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gaa27605972947c862397ebee40c2ff917</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int32</type>
      <name>XDAS_Int32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>gae431579ed9eff9134de78ca00ddd5f3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Uint32</type>
      <name>XDAS_UInt32</name>
      <anchorfile>group__ti__xdais___x_d_a_s.html</anchorfile>
      <anchor>ga615572fcd2279a6780dc1785d72ff421</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>CODECENGINE</name>
    <title>Codec Engine Runtime</title>
    <filename>group___c_o_d_e_c_e_n_g_i_n_e.html</filename>
    <class kind="struct">Engine_Attrs</class>
    <class kind="struct">Engine_AlgInfo</class>
    <class kind="struct">Engine_AlgInfo2</class>
    <member kind="define">
      <type>#define</type>
      <name>CE_NULL_algs</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga687607b8a6f12ca612707cb6d11583b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_DECLARE_TYPE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gac50d12c52d8d4aac6d76992454c2dad0</anchor>
      <arglist>(name, types)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_LOCAL_ALG</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafa86c420c31be63be93489ca63c7d174</anchor>
      <arglist>(name, algName, ialgFxns, idma3Fxns, iresFxns, groupId, memType)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_BEGIN_ALG_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gacf6ab4ebae6dd399688b98e13d21ceaa</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_END_ALG_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga115a7b326a0a7fde5127ad8a523b9763</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_ENGINE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad994d600966e4ba100cc710d5ab32af5</anchor>
      <arglist>(algTab, engineName, serverName)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_BEGIN_ENGINE_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab542c08643ed464fb2fb97882d72548a</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>CE_END_ENGINE_TABLE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga6d8741a755739533403cb5b151c5b1b4</anchor>
      <arglist>(name)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_GTNAME</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga11643a7e887b00dd2650bb1ca2732a7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EOK</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaf8bb60516b74105725e58412a88db1e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EEXIST</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga0f8fa096a63966a75462564312a3bd66</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOMEM</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3ee58dda6fc9f978795f3cea8e2020c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EDSPLOAD</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga1e606dbc394478386aefe4bc5b3abfa6</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOCOMM</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafe977b3ced21706146f17a13bf14ef93</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOSERVER</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga22591f7ad9c65dbff089ef9e1fbd9e85</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECOMALLOC</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4525910605d2e130d56375a1fbf68670</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ERUNTIME</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga432f689c4e041b891e1f684be26fb6df</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECODECCREATE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaf1540d3614ae2319c6b58e61ea9da113</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ECODECSTART</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3997d0a7c94029d986d65265c44d5ab7</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EINVAL</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gadfe8054a16e0d418121dbc85627907f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EBADSERVER</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga2439ba2928ca9b6fcdc07747103e6d8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOTAVAIL</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga12a509dcf682511e67b2ea55d44057a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EWRONGSTATE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga79536865c47e6bc79a29b4b0579b3767</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_EINUSE</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga94a32c2e92fe465e882d3f3ab28c3ab3</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ENOTFOUND</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaae6c26e072b54d7391d3e3e38156c0fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Engine_ETIMEOUT</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad11ff34d807f5333fd6da55c6e7c5d5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct Engine_Obj *</type>
      <name>Engine_Handle</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga959793a179df69888545ae97ea5133f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Int</type>
      <name>Engine_Error</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab52682a9391cdc982bed4d1182dd45a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>CERuntime_exit</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gae81e229a6d09ac5c102cf76bac61b5c9</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>CERuntime_init</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga624b5013c5e945115f1cb24d91e4bb1d</anchor>
      <arglist>(Void)</arglist>
    </member>
    <member kind="function">
      <type>Void</type>
      <name>Engine_close</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga59dcc500dd2d79d8b010966aaaa81168</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Handle</type>
      <name>Engine_open</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gab8727c3396b518f7ceb9b6deadd3087b</anchor>
      <arglist>(String name, Engine_Attrs *attrs, Engine_Error *ec)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_fwriteTrace</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4ce94c8f9c8d5a2e18b5e0b18babc0fb</anchor>
      <arglist>(Engine_Handle engine, String prefix, FILE *out)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getAlgInfo</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga48e46d28d6255d83df21f1b71046b6f1</anchor>
      <arglist>(String name, Engine_AlgInfo *algInfo, Int index)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getAlgInfo2</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga7bf5ed04f4f5b3c986afce20aa2fb123</anchor>
      <arglist>(String name, Engine_Handle engine, Engine_AlgInfo2 *algInfo2, Int index)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_getCpuLoad</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga490ba2a1ced016d81b382173ef45e36a</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getLastError</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gafbac0d441fe395cd5bd4766b11981653</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>String</type>
      <name>Engine_getName</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga4d3564bb008d9125ec552d38d882e4c4</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getNumAlgs</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga3e2dca6a4e33ab6e39360eb80e4be2ea</anchor>
      <arglist>(String name, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Engine_Error</type>
      <name>Engine_getNumAlgs2</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga7e91e8e5b6afd0381682cab6fae7fa6f</anchor>
      <arglist>(String name, Engine_Handle engine, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Handle</type>
      <name>Engine_getServer</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gad66457f2cf1c4689df5a861e82fdee0e</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>UInt32</type>
      <name>Engine_getUsedMem</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gaaaa0c364a45c1da8df0c9e1bf4aa66b9</anchor>
      <arglist>(Engine_Handle engine)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Engine_setTrace</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>gabb16d952ee17a7744ec84cb7e837f458</anchor>
      <arglist>(Engine_Handle engine, String mask)</arglist>
    </member>
    <member kind="variable">
      <type>Engine_Attrs</type>
      <name>Engine_ATTRS</name>
      <anchorfile>group___c_o_d_e_c_e_n_g_i_n_e.html</anchorfile>
      <anchor>ga189a5d439a3afb93d283e8476d504d60</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>ti_sdo_ce_Server</name>
    <title>Codec Engine Server Interface</title>
    <filename>group__ti__sdo__ce___server.html</filename>
    <class kind="struct">Server_AlgInfo</class>
    <class kind="struct">Server_MemStat</class>
    <member kind="define">
      <type>#define</type>
      <name>Server_GTNAME</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab264678f3ca17eb9c2ffacacd0b77bb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>Server_MAXSEGNAMELENGTH</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga305799c99b0eba1a69a5f37a0889346c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>struct Server_Obj *</type>
      <name>Server_Handle</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab249b418561d6d673a7412bd745408b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <name>Server_Status</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gafb6db0d25514e36fd10b4336c8388ac0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EOK</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0a97a8654b5c34c79f886d8aac27e8af0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOSERVER</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0afc59e30b03545a05cf9515e267454b32</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOMEM</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ae6efeda9864aae45b0b27dbf0ab85c7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ERUNTIME</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0aa2cb90e4b726b9e5413f0bc8fea3bc49</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EINVAL</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ad9d0d3e0a9e25a126984423fdc8c05de</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EWRONGSTATE</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0abb2d405c1d048bc9adc18b466711f067</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EINUSE</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ad3cd4be539595dcbe3b6ff22b055cdb6</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_ENOTFOUND</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0a908ab6d9de61932d2d18e92ca930d88e</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>Server_EFAIL</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ggafb6db0d25514e36fd10b4336c8388ac0ab412a9ccade194d093661fab07fdcaa9</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_connectTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga8c962a2b8c6c77d094f04a95867f6a34</anchor>
      <arglist>(Server_Handle server, Int *token)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_disconnectTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gac819d08852a05ce7e0b27b504717d2a7</anchor>
      <arglist>(Server_Handle server, Int token)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_fwriteTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gabf3d25f7f9043e7b1b9361fa30945c32</anchor>
      <arglist>(Server_Handle server, String prefix, FILE *out)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_getAlgInfo</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga4a452bdc479e8c0032638994589fc335</anchor>
      <arglist>(Server_Handle server, Int algNum, Server_AlgInfo *algInfo)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_getCpuLoad</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga286132d42e203cee6ffcd90aa350f0f8</anchor>
      <arglist>(Server_Handle server)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getMemStat</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga5ea4f6bfe49a820c18c41be08a5633ed</anchor>
      <arglist>(Server_Handle server, Int segNum, Server_MemStat *memStat)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getNumAlgs</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga1f8e0693b89cc1b2bc17be1ebd334216</anchor>
      <arglist>(Server_Handle server, Int *numAlgs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_getNumMemSegs</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga29b243a3787ef9a481b7c42fc9392170</anchor>
      <arglist>(Server_Handle server, Int *numSegs)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_redefineHeap</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>ga243526c5b7f2c05a42e794d41aef43f6</anchor>
      <arglist>(Server_Handle server, String name, Uint32 base, Uint32 size)</arglist>
    </member>
    <member kind="function">
      <type>Server_Status</type>
      <name>Server_restoreHeap</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gab655c3a9370796a8f5bf8b99ee3974ee</anchor>
      <arglist>(Server_Handle server, String name)</arglist>
    </member>
    <member kind="function">
      <type>Int</type>
      <name>Server_setTrace</name>
      <anchorfile>group__ti__sdo__ce___server.html</anchorfile>
      <anchor>gafa9cb503170965cf48160304d2b7c998</anchor>
      <arglist>(Server_Handle server, String mask)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Engine_AlgInfo</name>
    <filename>struct_engine___alg_info.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>algInfoSize</name>
      <anchorfile>struct_engine___alg_info.html</anchorfile>
      <anchor>ad5048fce8ebf0d0a66ccd3211f472c13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>struct_engine___alg_info.html</anchorfile>
      <anchor>a4a0f6b8cfa056b57af92fa5acc4e7b14</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String *</type>
      <name>typeTab</name>
      <anchorfile>struct_engine___alg_info.html</anchorfile>
      <anchor>a699567d7ce4c44514f5075a0a38dd86d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>isLocal</name>
      <anchorfile>struct_engine___alg_info.html</anchorfile>
      <anchor>aaffd686fb36bc5d1ebb3c44ee5f3c6e7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Engine_AlgInfo2</name>
    <filename>struct_engine___alg_info2.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>algInfoSize</name>
      <anchorfile>struct_engine___alg_info2.html</anchorfile>
      <anchor>a9127cdb52e85f2434aeac3616bd3c1ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>struct_engine___alg_info2.html</anchorfile>
      <anchor>a229ff1b6e4ae57fa306384afd30e93d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>types</name>
      <anchorfile>struct_engine___alg_info2.html</anchorfile>
      <anchor>ab7f6ff07a0b66ebae9f86527e31195c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>isLocal</name>
      <anchorfile>struct_engine___alg_info2.html</anchorfile>
      <anchor>abd1a7d4d4ff9c07512fb4e71979dc953</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Engine_Attrs</name>
    <filename>struct_engine___attrs.html</filename>
    <member kind="variable">
      <type>String</type>
      <name>procId</name>
      <anchorfile>struct_engine___attrs.html</anchorfile>
      <anchor>adf3cea83aaaf4a691862fd4872952a70</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Fxns</name>
    <filename>struct_i_a_l_g___fxns.html</filename>
    <member kind="variable">
      <type>Void *</type>
      <name>implementationId</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a83963e2ca17632c15bdb01494481a615</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algActivate</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>af1213efc8ac6fdfb72b50da9950baaa7</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a1640ba8f4033af1ce3887283c7a12746</anchor>
      <arglist>)(const IALG_Params *params, struct IALG_Fxns **parentFxns, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algControl</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a4c506a1599a604b02b30097e61ff4b89</anchor>
      <arglist>)(IALG_Handle handle, IALG_Cmd cmd, IALG_Status *status)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algDeactivate</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a10f29860ab8b3beab69b0f0128c3d969</anchor>
      <arglist>)(IALG_Handle handle)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algFree</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>ac6f87b240d96486e3e88e80b95046ade</anchor>
      <arglist>)(IALG_Handle handle, IALG_MemRec *memTab)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algInit</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a94eca7c58cceb112eccd970a6cf3f569</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Void(*</type>
      <name>algMoved</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a5456c5087825b808e18000c551a66ef1</anchor>
      <arglist>)(IALG_Handle handle, const IALG_MemRec *memTab, IALG_Handle parent, const IALG_Params *params)</arglist>
    </member>
    <member kind="variable">
      <type>Int(*</type>
      <name>algNumAlloc</name>
      <anchorfile>struct_i_a_l_g___fxns.html</anchorfile>
      <anchor>a098c1ca275465bb4acc1d3d0cf060160</anchor>
      <arglist>)(Void)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_MemRec</name>
    <filename>struct_i_a_l_g___mem_rec.html</filename>
    <member kind="variable">
      <type>Uns</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a6d4138068c5a30b4399464f5a8e3aca2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>alignment</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a86daec3754a4b918fff07efe28461748</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IALG_MemSpace</type>
      <name>space</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a41e307f25d01a4329f4f4bd794c9087c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IALG_MemAttrs</type>
      <name>attrs</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>aa9dca3a637dc7e26069f4a11e7c82593</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Void *</type>
      <name>base</name>
      <anchorfile>struct_i_a_l_g___mem_rec.html</anchorfile>
      <anchor>a2a51de211c96021ca4aa360e352aa90f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Obj</name>
    <filename>struct_i_a_l_g___obj.html</filename>
    <member kind="variable">
      <type>struct IALG_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_l_g___obj.html</anchorfile>
      <anchor>aa80d0fb968dce61561689d3793bd5b6c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Params</name>
    <filename>struct_i_a_l_g___params.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___params.html</anchorfile>
      <anchor>af8fa239e38c54b8202e30292e99089c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IALG_Status</name>
    <filename>struct_i_a_l_g___status.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>size</name>
      <anchorfile>struct_i_a_l_g___status.html</anchorfile>
      <anchor>a852361d0183829e930a949268d9b0b02</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_DynamicParams</name>
    <filename>struct_i_a_u_d_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a62cb7a2795bc2071990488110d388a83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>downSampleSbrFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a7eba84061f598eed30d8167425533187</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Fxns</name>
    <filename>struct_i_a_u_d_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>ae84c356dd54c0dc761fb09d62d1da414</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a45764e3d0bdcbdda81515faecc1253fc</anchor>
      <arglist>)(IAUDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs, IAUDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a0669353a289747a5e1e4eec31ed55a21</anchor>
      <arglist>)(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id, IAUDDEC1_DynamicParams *params, IAUDDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_InArgs</name>
    <filename>struct_i_a_u_d_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a365f92b03f0d9aa2e7a9aba991a0e157</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>ae18cbd70e339b8eb6f1218d4d568342d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>desiredChannelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a0e92ea373b568bb9b01fc597ea9328bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___in_args.html</anchorfile>
      <anchor>aa883674ad2acf2783bd6ce5dc814f3ee</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Obj</name>
    <filename>struct_i_a_u_d_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___obj.html</anchorfile>
      <anchor>a3c9d38b9e3bea6d67ec63ade24103c5f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_OutArgs</name>
    <filename>struct_i_a_u_d_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a7c96524400bdc69520d551556d90d2ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ae2c89e897af375c11ecf4a9cf1efa20e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>aa43125deb8cd6ebc4cb52349d1d3706a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numSamples</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ade0b9c3e6a1af7efa3b643c37f47011b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a656b5500bc0c66e36038f71d38904599</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a31afcddf15d8a63834c6d6859c85c788</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>aeb55f5e3fd6c23e5f428b599d63af23f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a34c8f7cca4b8fc7c9aaf4efd4c386a0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Params</name>
    <filename>struct_i_a_u_d_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>ac3e81428345ce8f38072b84f0915a630</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputPCMWidth</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>a30d01ee3e225da6d3f38d40fa3ab6e20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>pcmFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>a9e01bdc5d85fe05c3359fc61ae922674</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___params.html</anchorfile>
      <anchor>ad574cb974d9171e50681d4ba1d73005d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC1_Status</name>
    <filename>struct_i_a_u_d_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a826bd51574317cd6454992edd2bb90c5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a1206c6c4de6b6ab149d6e9502593a736</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>ae945132c2fcc18cbfa0a2651ffb2e00f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>validFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a799fead5a0069edef26fe4db6c0a3a67</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a31f366f22b6be11a265997894ee2882d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a0b3807ad0e57a843c931a6fe4dc5dae8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>af7bb03870761a517669ddb3a1c074f27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a31e28d7e4f0d6695a75db5cd8e334981</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>pcmFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a8f483fe1584f0586fa1c7a8870485376</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numSamples</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a85478d6381cf013ecc6da9c1152fa01b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a059f98573ce856e21685533ca92e5213</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a27c19357781a5f50808b84d590b702dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_d_e_c1___status.html</anchorfile>
      <anchor>a4781ae1f91603c4e2abfee78eb22590d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_DynamicParams</name>
    <filename>struct_i_a_u_d_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a3efdf1a5413ab93b0683871995b261d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a77c203a30a88437d6ef39a909ee79a98</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Fxns</name>
    <filename>struct_i_a_u_d_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>a7d21b3a9a68e97547db2622d31e5e072</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>ac4c542a8b025b2eb9625ef3fc0b4eec8</anchor>
      <arglist>)(IAUDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDDEC_InArgs *inArgs, IAUDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_d_e_c___fxns.html</anchorfile>
      <anchor>a58c2671fe58764d1efb786c55033e6be</anchor>
      <arglist>)(IAUDDEC_Handle handle, IAUDDEC_Cmd id, IAUDDEC_DynamicParams *params, IAUDDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_InArgs</name>
    <filename>struct_i_a_u_d_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___in_args.html</anchorfile>
      <anchor>aff9bb0f0b05b08f11d4e63dfd59292ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_a_u_d_d_e_c___in_args.html</anchorfile>
      <anchor>a5779c96d5ac6b17bb72d8130c6012220</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Obj</name>
    <filename>struct_i_a_u_d_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_d_e_c___obj.html</anchorfile>
      <anchor>ab4599f02c2e0ad7374f5cab60144b975</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_OutArgs</name>
    <filename>struct_i_a_u_d_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>a636d9cf7182daa83dde40b91503cb7d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>ab36a174af0ebd1260366a2a3d6c420b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_a_u_d_d_e_c___out_args.html</anchorfile>
      <anchor>a36f1f3942a95eb2e0ef5a5abdfe18ce1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Params</name>
    <filename>struct_i_a_u_d_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>abefd49970a0d7019a2149caceca25202</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxSampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a1d17ef20b3588b611da85987f190f051</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitrate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>aaec1f709e08221e4c57918f1cedba413</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNoOfCh</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a7734e3b82506ac1984fb192d1570d2dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_d_e_c___params.html</anchorfile>
      <anchor>a1026e2790111047eb5abf97981eb24af</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDDEC_Status</name>
    <filename>struct_i_a_u_d_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a3ac44e0a364b869ade33de2367041eb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a92e4be96393ae49b63dd903046d45207</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a6ac5aa3f76443a4af8bf371ddfef2a1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a308118960ef09f2d09efd00b0960b4b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numChannels</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>ae8b964499514d8faaee5a705e2a27c38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numLFEChannels</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a651beebf6269ed638c061deb6110ed20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFormat</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>adf26589fae5a43e85c1d75fccc7fc5f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>autoPosition</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a5e88a20c8f23cbacfcdc6f3e4f4888d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>fastFwdLen</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a26aca932d0dd5b45e55b672e10bf2daa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameLen</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a12fbec1763df3e9927173b67fad59ac4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a8c1e5dbdd574b862d6496e17d7072e9e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_d_e_c___status.html</anchorfile>
      <anchor>a85d70038b7e369f13f0d38a9464dc959</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_DynamicParams</name>
    <filename>struct_i_a_u_d_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a38669fd83b7e8bafd7df795ffba90e81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a2f9a6d0fc78715b6f011279974b60e09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5d1a59bfc159d8bb5295e2e3c50e3b5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a282afbb193fb496790a1be716e4150ac</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a3e0ff85b937bdf6cadcbfc9a2ca1044f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a07ce37dda31a8610bea11d291dc862c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a48a91dff3b69d89222787dfa0f942f96</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Fxns</name>
    <filename>struct_i_a_u_d_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a7bf4105d2612bc042264f0cf82664522</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a2175ac4f31d6428adcdedff1adbe4ca1</anchor>
      <arglist>)(IAUDENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IAUDENC1_InArgs *inArgs, IAUDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a5174d4a35ad3697b070c88fe863f7c7d</anchor>
      <arglist>)(IAUDENC1_Handle handle, IAUDENC1_Cmd id, IAUDENC1_DynamicParams *params, IAUDENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_InArgs</name>
    <filename>struct_i_a_u_d_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a5a94c918431ae8a8de2062b475743225</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInSamples</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a19afbc4c865d2c67145e9fa34bdc44ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>ancData</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___in_args.html</anchorfile>
      <anchor>aaacc03a3126aff730e2efddce672088b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Obj</name>
    <filename>struct_i_a_u_d_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___obj.html</anchorfile>
      <anchor>a09b3f5bf9282709ddb3271a67b9b419b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_OutArgs</name>
    <filename>struct_i_a_u_d_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>ad8ae4ff0472af0f3c4d0b1460e6f62f2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a786ad251b077d9ea2fca7ed2a439737c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a602245d6b2522cdf47602e52f6abd9bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numZeroesPadded</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a1a66bd054185791eec49e7b23b32014f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInSamples</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a624915bcdafb599bfc65c3ead26a5207</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Params</name>
    <filename>struct_i_a_u_d_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a863c8890eba38e149b9babd74b64472f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a55b8e1d5f54dbd7ce3f7935bbf42be4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>af441094e0b6b7e080c39404a99298b6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ad6585c74128f70787cef03e3d51f64f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a42ee7259bc8041c7b653b452ffbb526b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>aeb577e33a8a9cc3ed2895e7e55d64a4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFormat</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a47267b88d7d0fbfcde6021abc876cb2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>a12495c4f1e6b27a024a79229a33c82cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>acbf7c107c1fee67764c066a33c221b53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dualMonoMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ac0db971806a5564a262fea039168f338</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>crcFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ad8360020e2a4ee0d72175c3d6dae91ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ancFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>acced022f0aafffa576aebfe45bf0774b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___params.html</anchorfile>
      <anchor>ac8289c3bd4154b9f10fb86c169cdc33b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC1_Status</name>
    <filename>struct_i_a_u_d_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a90db5b78e9f03f587a79978453866247</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a32d98a3c40437e07a9fcbea86257bd48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a342aa2f4ef1e90bd55d6878d4cd65984</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a8d18605b6f4ddec8301e5677f50ede13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>validFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a24c7cd3c841eaf2c94517b8eae61958b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>lfeFlag</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a1a0e020552be775cf6889f8997dc5575</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a4764128db2b65d1c8b7b160e5a3c7663</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a524d800bdabb32aaf50cf719c0615e13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>channelMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>adf6a73a1aaf242ccc9f57831bc14fc13</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encMode</name>
      <anchorfile>struct_i_a_u_d_e_n_c1___status.html</anchorfile>
      <anchor>a30b9ac5fa09ccfb1e3e5e584dbc39812</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_DynamicParams</name>
    <filename>struct_i_a_u_d_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aece1b773849b274e83937c90afcfbbd6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFormat</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ab3bb1b4c908f342a66746ec4812c8a03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a7e69f9c93e5fe34ab54226aa9efeacc7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>sampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2551605459f2a3380045bef36eeec318</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numChannels</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4d6ef3837f6e4a466a53fecd5ada26b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numLFEChannels</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aa07be071f60ec426a25fdc7daa2d7703</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputBitsPerSample</name>
      <anchorfile>struct_i_a_u_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a845c8c4530de9b87179338c5116e170f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Fxns</name>
    <filename>struct_i_a_u_d_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a76c6c607f10d91ffcf5a8288a14f6e1a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a6ceea92a81bde38833a084999912a721</anchor>
      <arglist>)(IAUDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IAUDENC_InArgs *inArgs, IAUDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_a_u_d_e_n_c___fxns.html</anchorfile>
      <anchor>a30ecbc7373f4ad3c0f7eba39ae7ac585</anchor>
      <arglist>)(IAUDENC_Handle handle, IAUDENC_Cmd id, IAUDENC_DynamicParams *params, IAUDENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_InArgs</name>
    <filename>struct_i_a_u_d_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___in_args.html</anchorfile>
      <anchor>af1063c6ebc40bb5e0666b3bd4f4aaa39</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Obj</name>
    <filename>struct_i_a_u_d_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IAUDENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_a_u_d_e_n_c___obj.html</anchorfile>
      <anchor>a95d82873d8c890474e61acb69022996f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_OutArgs</name>
    <filename>struct_i_a_u_d_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a8617cbe09b473159306623e0ab8e7664</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a84d7cbd368a512d72797ef1b295c3c83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_a_u_d_e_n_c___out_args.html</anchorfile>
      <anchor>a7cc460eba6286f3c0c72e648e4a72c3e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Params</name>
    <filename>struct_i_a_u_d_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a121321ce5cfa852dbad28d1c5bbb3dff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a23b6f1b1e86535831b5c3907d78765b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxSampleRate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a0c62620ea85d3e7f3f0e059f9450afa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitrate</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a302736e97cd0a8473e850bf981dd58f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNoOfCh</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>adb1a33f7967138a4af5f2fe2696fee58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_a_u_d_e_n_c___params.html</anchorfile>
      <anchor>a9d1edc1ea5e41a532906f8740b85da46</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IAUDENC_Status</name>
    <filename>struct_i_a_u_d_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>aeee4d26ddd0bf88fc0d02afc49e72e61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>a446f27ae2c13dde94db6c99c8b65f7dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameLen</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>aed3f3896aa0d2692de7acbb69bfcd6ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_a_u_d_e_n_c___status.html</anchorfile>
      <anchor>a2d5481a11c8b9b7d51b03b9e548a7d9e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_CodecClassConfig</name>
    <filename>struct_i_i_m_g_d_e_c1___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___codec_class_config.html</anchorfile>
      <anchor>a9f06638477cfb065b7ad154a6b4f1bf3</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___codec_class_config.html</anchorfile>
      <anchor>a598741bd03aceeb9f8138e9bf08a5092</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_DynamicParams</name>
    <filename>struct_i_i_m_g_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa4c9d6477d1b69da4a794235a9372dec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>ab090944f3fe152ff41db1ac355ba991e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a314c9a6c607b0717bb279ef154887322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a4ab23a661fb362efb4908096191db7bf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Fxns</name>
    <filename>struct_i_i_m_g_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a1673d23b38f9e6977a33b53aa65a923e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a13a91dc7eef87f708ddcfd547ff27d04</anchor>
      <arglist>)(IIMGDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGDEC1_InArgs *inArgs, IIMGDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___fxns.html</anchorfile>
      <anchor>a5286ec4d1f0ac863a44908f68eca2995</anchor>
      <arglist>)(IIMGDEC1_Handle handle, IIMGDEC1_Cmd id, IIMGDEC1_DynamicParams *params, IIMGDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_InArgs</name>
    <filename>struct_i_i_m_g_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___in_args.html</anchorfile>
      <anchor>aea309a5bfa38760ab68185646ed4e9c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___in_args.html</anchorfile>
      <anchor>a9b784b066b2ec561358f36394ccfa1d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Obj</name>
    <filename>struct_i_i_m_g_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___obj.html</anchorfile>
      <anchor>ad6d0a0e1c1ca47a5eac48d91c1109605</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_OutArgs</name>
    <filename>struct_i_i_m_g_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>af2ec3b3eddf342cde6f9980439bed26f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>acc8c984f3d9480504d47416f523fad91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>ac02d0a13f9df372d84b6799da82a3bf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>af21d67faba69291bdf538e058cf97288</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___out_args.html</anchorfile>
      <anchor>aa0beab4e9cb5cef8c62a85574dc14930</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Params</name>
    <filename>struct_i_i_m_g_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a68ef28de7eeb2c1be8109d74a851f4ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a28a9950c839329471d708f4e176171a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>aade2a8cf1f3ccdb0d980938261ddd37d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a7c103d1347316a69abae2190b8dea17c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>aaeef8352b4a4f9da7c78ff5822eee807</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___params.html</anchorfile>
      <anchor>a72c85f144a784198e26b432964f1bdb1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC1_Status</name>
    <filename>struct_i_i_m_g_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>af59caabb4e4ccc358630e6b363c107fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a37dfba8ab0c467adb7f6c1db717ecab6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a81ec5049fd6fa9600a624832e278f71e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a56f796a7a31a85e509398e7b16710885</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a4ac439b05ac11c19f601830757a22c65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>imageWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a1307dd910542f436544c4d323a6ae1eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a22a4a4cc9e80680bc8b7c8c0748e5130</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a5179894a90ac9dbccee34da8f9867b11</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>acb0416bbc4b12fc1ed47e8884a2841f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_d_e_c1___status.html</anchorfile>
      <anchor>a390e30541edc5cf2e8c1e34861acdf50</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_CodecClassConfig</name>
    <filename>struct_i_i_m_g_d_e_c___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_i_m_g_d_e_c___codec_class_config.html</anchorfile>
      <anchor>a6ec49d374ee53ca2351a82919eb64d93</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_i_m_g_d_e_c___codec_class_config.html</anchorfile>
      <anchor>a6cb4aae806b6957fba9a7bbf4430c80f</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_DynamicParams</name>
    <filename>struct_i_i_m_g_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a254655a6ad7c7193c53f999347aed127</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>af065eaae9f3739fda81e8825984c9ef2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>aae784db8ba465f6a24a79a7acd47a0bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a31786a33a7a9c554184e9c6dfe0db690</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Fxns</name>
    <filename>struct_i_i_m_g_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>a8e416fe391cd2f3105d31f222d1ba2e5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>a31fb7fbbffe4e089edf33b837bcc0118</anchor>
      <arglist>)(IIMGDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGDEC_InArgs *inArgs, IIMGDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_d_e_c___fxns.html</anchorfile>
      <anchor>aa6fd366aa0ffb9739bbcf76236f56a48</anchor>
      <arglist>)(IIMGDEC_Handle handle, IIMGDEC_Cmd id, IIMGDEC_DynamicParams *params, IIMGDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_InArgs</name>
    <filename>struct_i_i_m_g_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___in_args.html</anchorfile>
      <anchor>ab9f89a0eb8c44316d89b8e756fb4fbe0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_i_m_g_d_e_c___in_args.html</anchorfile>
      <anchor>a1b87bd7c64b4eae54f0242969171c97a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Obj</name>
    <filename>struct_i_i_m_g_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_d_e_c___obj.html</anchorfile>
      <anchor>ae8899a18eb4544d8df8cd7a169650d5b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_OutArgs</name>
    <filename>struct_i_i_m_g_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a184969265be2f68bd8057ce80787a858</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a8674f98d668855ebc621403037ac923e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesconsumed</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>ab61e84a080a3b4a694b26cd281f40614</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>ac0b707601295096111ff8d68a768f0b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c___out_args.html</anchorfile>
      <anchor>a1cb086ad5fca07497045e8048602c7d9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Params</name>
    <filename>struct_i_i_m_g_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>ac4d727a2d02d60c16fb9a14c0ff2b49c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>aebd38c58951121af2fa1f065ce3850b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a857319dc296cde870cd1ae319d843bdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a535ad75b4f0ba9b6a71d974006ef47cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a845a59a3956acdaba154eb3a3db1e872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_d_e_c___params.html</anchorfile>
      <anchor>a221f6bf52d0292e0a7aa86155c3fa8c6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGDEC_Status</name>
    <filename>struct_i_i_m_g_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ad0152f6a4cc1559e839ea46d345fee71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>aa915f496c44181936937111c063d514c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ac548c3f2d341ee948e9882da5dbdc43a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>af2e8f4997fe73adb906fcead9326d589</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>imageWidth</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a3181d0dcf4d20c8c616de7c14102a686</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outChromaformat</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ab3c00954da4df2698d841e32dd4e6b2e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a4eac921b7c6ee4521c38e84f35c7f279</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalScan</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>ad33c5c68bd43da2c542a5071d5425b5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_d_e_c___status.html</anchorfile>
      <anchor>a68ebe9eb6f5f695e0cfd9b3d5959338d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_CodecClassConfig</name>
    <filename>struct_i_i_m_g_e_n_c1___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___codec_class_config.html</anchorfile>
      <anchor>a7e5e9db7894956eeb43f953933027cc7</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___codec_class_config.html</anchorfile>
      <anchor>abfae3fdd177fe001dc0b089375deb3cb</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_DynamicParams</name>
    <filename>struct_i_i_m_g_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a204c149d672eb0ec2a804ed32b5f4f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a399b147e439c80078ff6eb90f64867bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5997bc006ae260875c03bba4822ef831</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5dff404be26d01f893c9a949f398c2eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a2f98fa2e18ca9e574b4ff03a835cd673</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a596b0b97d9470d219cb42a39dc7d0131</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a0bc97e319bfced1788bc7fbe2beb426e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>qValue</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a5acb90b702778906448f36559cf0db0c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Fxns</name>
    <filename>struct_i_i_m_g_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>a96bab6b9557586374244a47decc33ac7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>aa54e936ca1e55be977939d0bcb932675</anchor>
      <arglist>)(IIMGENC1_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___fxns.html</anchorfile>
      <anchor>a21fd3831f13a37f9944b09269599406a</anchor>
      <arglist>)(IIMGENC1_Handle handle, IIMGENC1_Cmd id, IIMGENC1_DynamicParams *params, IIMGENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_InArgs</name>
    <filename>struct_i_i_m_g_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___in_args.html</anchorfile>
      <anchor>ab5daa9ec3ed4ebfc98b97a7071bcdd83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Obj</name>
    <filename>struct_i_i_m_g_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___obj.html</anchorfile>
      <anchor>a6e7640244d9414cc018dd20a4f493b28</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_OutArgs</name>
    <filename>struct_i_i_m_g_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a97fad74938d4965d2a7d287dae43cbf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a950a903ecd2280b1f5d1a557ec011a53</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a5475f48ec868746d031f014da5d9c6e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___out_args.html</anchorfile>
      <anchor>a3e7a1946235ba233f417193956a37373</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Params</name>
    <filename>struct_i_i_m_g_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a835e41b45a222e18f987d4baa8cdd8c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>aa403e29e6bdf59d846d47a4993488113</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a7cff78e35b12cb9a5108851a482bcada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a552ff0784420f66be77a8a74e7220abe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a7c3d94b5c755a3bef6b11848da0224cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___params.html</anchorfile>
      <anchor>a9effdda884dcdf570e82549d9fb06908</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC1_Status</name>
    <filename>struct_i_i_m_g_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>af9d5e1bc284efefcb16dc83bb967eb54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>a74178f2a698da0e8ff167404d362a461</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>ad2e308395a24a1eaef3b7329f6cb819f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>a92330058d2f29b19d6af03879e1db231</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_e_n_c1___status.html</anchorfile>
      <anchor>aba6710131d4c45e1d66edbfed3a1cee9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_CodecClassConfig</name>
    <filename>struct_i_i_m_g_e_n_c___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_i_m_g_e_n_c___codec_class_config.html</anchorfile>
      <anchor>a51231d81824cb841bf9c439b9cea77a7</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_i_m_g_e_n_c___codec_class_config.html</anchorfile>
      <anchor>ad872c95e7cfedf317932be174b85e6ca</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_DynamicParams</name>
    <filename>struct_i_i_m_g_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a917db70323ce8e73f24eb2d48765d599</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ac881f6fbd5aff7fea90b226cd65570e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>abc6397cc8192155d63a626f14a3046b6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4d0f6a5b443c13145c993ccb201e5904</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a7a0c2a88716feb3b60eb5eb875cbfed1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a4955921c6b4ceeb20f54b6337cbfdc93</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a51769be40d35f6de0e7189794da61683</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>qValue</name>
      <anchorfile>struct_i_i_m_g_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2776a330ed24ff7d009c10ae158b0aec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Fxns</name>
    <filename>struct_i_i_m_g_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>a9e2a218029f6f8dff34b312b519bcdfb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>ace8cdefa23da4b6168834ca386bd2de4</anchor>
      <arglist>)(IIMGENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IIMGENC_InArgs *inArgs, IIMGENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_i_m_g_e_n_c___fxns.html</anchorfile>
      <anchor>a0ed53076380f314058c68dc5b6b0e9f8</anchor>
      <arglist>)(IIMGENC_Handle handle, IIMGENC_Cmd id, IIMGENC_DynamicParams *params, IIMGENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_InArgs</name>
    <filename>struct_i_i_m_g_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___in_args.html</anchorfile>
      <anchor>acd1a68fd6621f915df4bdabfe994387d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Obj</name>
    <filename>struct_i_i_m_g_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IIMGENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_i_m_g_e_n_c___obj.html</anchorfile>
      <anchor>a3ff20a14f6b60864f563bcf5af0eca02</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_OutArgs</name>
    <filename>struct_i_i_m_g_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a60e743c4af4f564dcdf85649759902d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a95e9f3335445d1a4114d4d993f4d5ba6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>a17bc924d654d6feb65f154c4a096c075</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>currentAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___out_args.html</anchorfile>
      <anchor>ac8c6a91a72d4cdadbacdfa2fb18f1e81</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Params</name>
    <filename>struct_i_i_m_g_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a6c6bd3222a36f376344d1bdd882679a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a8d5646fa9ada0fb55c21783c9d54cb3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>aad4f389bbc2ea97a487aea0b9d8b60fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxScans</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a7e9f93fb240043a66dc3022220bad74e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a9c19691c3ab4f617a6b3d98087b8bfcf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_i_m_g_e_n_c___params.html</anchorfile>
      <anchor>a6377413cc5d331424b12b50264ac4711</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IIMGENC_Status</name>
    <filename>struct_i_i_m_g_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a5552865d6cb4558209650d9224eedd4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a4bcea737f9177a0458c7844f8893d9d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>totalAU</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a6575078c14a7632304b47902bffa6eec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_i_m_g_e_n_c___status.html</anchorfile>
      <anchor>a4df69be928122e608cc562d464cc6bdf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_DynamicParams</name>
    <filename>struct_i_s_p_h_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa80dbc4b1adab84f34bdfc87f20dba59</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a2011eaca87837ea467fc5c160ac4ad01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Fxns</name>
    <filename>struct_i_s_p_h_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>ae8f8acf1b191b805ee9ae2ce749d72ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>a1528fd9997b1c8f10b4f0e90e41f2984</anchor>
      <arglist>)(ISPHDEC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___fxns.html</anchorfile>
      <anchor>a83d133bb27e0e59f5edefc327cd87c18</anchor>
      <arglist>)(ISPHDEC1_Handle handle, ISPHDEC1_Cmd id, ISPHDEC1_DynamicParams *params, ISPHDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_InArgs</name>
    <filename>struct_i_s_p_h_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a45573006d595ec7e02613c1ac23426b4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a9ede028467059e0d566bafe42933966c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___in_args.html</anchorfile>
      <anchor>a3a54f5846955c1f79d11e4b90cd75bc5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Obj</name>
    <filename>struct_i_s_p_h_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___obj.html</anchorfile>
      <anchor>a820bfb1636e6112b60185a66c8dcd80a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_OutArgs</name>
    <filename>struct_i_s_p_h_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>a9072041fcbbf6aed30c2c286f1a31709</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataSize</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>af5f61f240741989786abb67ac599fb08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___out_args.html</anchorfile>
      <anchor>a31dd580740fa35e7ee89953bfcedbbce</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Params</name>
    <filename>struct_i_s_p_h_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a150293e4c3110f3d4d076e0408d2a9ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a86b1a7c0a3097ba622357b46649580c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a6a12afd16b8bcb17b0e6a7297c3131fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>adc0e9a85ccf92a99e57d9a40dc1b94df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>adb1b22225f324f421d0552078c727e34</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a0e95534b18d38e18a2ae953f08d62b72</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>tablesPtr</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___params.html</anchorfile>
      <anchor>a7bdee67fcfdecaa52441dbc7d597dd54</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC1_Status</name>
    <filename>struct_i_s_p_h_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>afcf7cc947701f22368d207b5e131554c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ad5dd7e6a43220b9fb692b1d4a22eaa3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ae3e61248edeeaaa883da2c9e9d1e6e68</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a43828548e9cbe9f8d9d3e68f34211322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a4d95d33d7e021796289df9a0a292fdb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>aac6319cce34942d24a437d0f4e121a1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ab6ac3e7ce838a59fb108df9996c3d66e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>a2b7136b6d521d7bee05cf824fb7b0b57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_d_e_c1___status.html</anchorfile>
      <anchor>ac3acec4581c20c9a44536da145cf9ba8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_DynamicParams</name>
    <filename>struct_i_s_p_h_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a69d0c7eb681ba0e6b3f0ffee99f2a867</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c___dynamic_params.html</anchorfile>
      <anchor>af345bcd1722adcb770f9817fb2cd44bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Fxns</name>
    <filename>struct_i_s_p_h_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a26f77c1d91e749fd168f047a3c96d799</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a5503c387e8d4d0c19bac44502262a3fa</anchor>
      <arglist>)(ISPHDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHDEC_InArgs *inArgs, ISPHDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_d_e_c___fxns.html</anchorfile>
      <anchor>a68fb3f93b8b7043dc1fe6e3e14f03a65</anchor>
      <arglist>)(ISPHDEC_Handle handle, ISPHDEC_Cmd id, ISPHDEC_DynamicParams *params, ISPHDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_InArgs</name>
    <filename>struct_i_s_p_h_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>a4d51fb5ac0aa12cf3a80f7ccf008b8b3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>ab7c8a4c2eaac00268c7655c5f5a48fda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inBufferSize</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>abb3ac1b9a729328cd7ce7aa8f7045798</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bfiFlag</name>
      <anchorfile>struct_i_s_p_h_d_e_c___in_args.html</anchorfile>
      <anchor>aa61efbf8cb2a0a6796de0f74a3d150e5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Obj</name>
    <filename>struct_i_s_p_h_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_d_e_c___obj.html</anchorfile>
      <anchor>a54f99ede68e33cecc93c7e4e236af75f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_OutArgs</name>
    <filename>struct_i_s_p_h_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___out_args.html</anchorfile>
      <anchor>ab538e6e2fb343331efae12ff703ccf9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_d_e_c___out_args.html</anchorfile>
      <anchor>a359a57b1de038428926e31b4b700dd49</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Params</name>
    <filename>struct_i_s_p_h_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>ac229d338e2023f649ec9f5a919ce7af6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEnable</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>ac3fcf69d59409092de9fac52f16d8424</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>a05b1acdd03d9afc0889c21287a6b20e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_d_e_c___params.html</anchorfile>
      <anchor>a17361b8876ba4566cd049cc14f364349</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHDEC_Status</name>
    <filename>struct_i_s_p_h_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>ac9ba939e27d759b58681209896404f7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>aaa5760ae19aadf956429f768d59dd3c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>postFilter</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>a4f6a588c75a2b2c1954dd0ca035c69ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataMode</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>a09c625c1d8d5da7403d5feec6d2bc091</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_d_e_c___status.html</anchorfile>
      <anchor>ab5bd8caf50e5ac128ae7a3fdeb57e81d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_DynamicParams</name>
    <filename>struct_i_s_p_h_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aed45782060e60f187f0feadd0c789a8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a4437394a8d96b7fa06dd52713414878b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae1373dedffee3604fb2cec5f4f4ae237</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a30e446e8f1a7f5eeb41e30f7feefc044</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a92326b689b7849a2e88fec8b87e5a641</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae77ce3b38ad8d6b3ee8e3f36cc826776</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a9605fa7c93a86e744dfe1360b0b39f21</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>abb206a3c91bd2482ae51bb9ab99ed41a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aedfa37091dbde8ef4b7ebf50ee7b312e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a996dce6c5654b65aac19600fbc805e13</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Fxns</name>
    <filename>struct_i_s_p_h_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>a6a14f0e7d1a8641cf5f22be8b21d6ed4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>a43e82ca6e0fa6e80f9f9e77b41d61362</anchor>
      <arglist>)(ISPHENC1_Handle handle, XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs, ISPHENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___fxns.html</anchorfile>
      <anchor>ad9db876aa3817ce0d4c302836b752e01</anchor>
      <arglist>)(ISPHENC1_Handle handle, ISPHENC1_Cmd id, ISPHENC1_DynamicParams *params, ISPHENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_InArgs</name>
    <filename>struct_i_s_p_h_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>a8795bb208ec9aa0838210f60192740e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>nullTrafficChannel</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>ab4b97eb4d6ec791504cdfb7bae5175a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___in_args.html</anchorfile>
      <anchor>a5a0c3ba88718f5ea6b7615e843f021e0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Obj</name>
    <filename>struct_i_s_p_h_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___obj.html</anchorfile>
      <anchor>a8daccb2c03641870da2c5ea613d516d2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_OutArgs</name>
    <filename>struct_i_s_p_h_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>a10a1dc52e2670c743435650cefc64e69</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>a3b3756aaa580605720e141c2b181742c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___out_args.html</anchorfile>
      <anchor>ab60d44742ed5bcb09c76c185b7890f01</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Params</name>
    <filename>struct_i_s_p_h_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>ac3ed9cc730c55ded22ca0106eb8c7b81</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a3c0fc73a4453be910b7fa7f839cd6bfc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a294eb4a70b58ba4855d6a7be6edcff25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a00bcdc92adaca6dde2e016fcd67d977b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>aa9e0f5bd11b4139a668e70a8e12c1f55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a61a56a09221795892a17d263791e7e4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a8ee2d360abce8bce78fcbcfe64096a38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>reserved</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>a6e7e4a4b1ddf71036b1924efb656c490</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>tablesPtr</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___params.html</anchorfile>
      <anchor>af97ca42a83ab32b534d96fa7c1f79c5d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC1_Status</name>
    <filename>struct_i_s_p_h_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a89a6a1e91831b571a7c8307b03983385</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ab642b0e66c77e4cb23b2fc6d6d985842</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a966d94b3e82336d3bae68d371c2c91b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>aaf8b77469771204141f263a50fc21ddf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a6331d68b41434a85591adade72ed5dbe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a580eb5e7ec546e662d624fb1264ee234</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a25a68e90cdb9c2a3dfbd6a4f40418da9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ad62aee90031890bac72c38f8cdb6f77a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a09cd795e3aebe95dfccded3b59dd6ff1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a3ac6b41cbfd395e7e04a53a646388f5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>aab6fb0582c9e6dfb74a0a3918bd60286</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>ab1497f19b4f3892b08741d6ba997ce3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a0c83f887a70d682870b1ab12624463e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int16</type>
      <name>codecSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a73c4340fd3e638c3e68fa4dde57b871f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_e_n_c1___status.html</anchorfile>
      <anchor>a97430d5b68ed94e0ac72b5055688890d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_DynamicParams</name>
    <filename>struct_i_s_p_h_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ae9c89ae7ddabe50e8859d551972d498c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a2281e59eb159955391c4ff4671912f0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a0f2a2397c0da0230024b3cf728c20fc3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>abc9eb329f94aa7fa8b1ab8e1d373c6da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a800e821077e744a3bafe40c012d38a99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>af307f8dad51fdc45b99b187f2dd18cb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a52ef158dd0c071bae86ec620eba81cb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a8d4619f29a70e5adec01566a44b8d6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a9fe622f273a17ed40140f4110b6666f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>homingMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a95466225694803c1cb293591f7d85710</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Fxns</name>
    <filename>struct_i_s_p_h_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>ab4b06da0cf49039ff6b4082044a2b4e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>a0e9da2ef8390270414527bdcf5c3fbb7</anchor>
      <arglist>)(ISPHENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_s_p_h_e_n_c___fxns.html</anchorfile>
      <anchor>a5003aafa401748cc192937e0f2f60506</anchor>
      <arglist>)(ISPHENC_Handle handle, ISPHENC_Cmd id, ISPHENC_DynamicParams *params, ISPHENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_InArgs</name>
    <filename>struct_i_s_p_h_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___in_args.html</anchorfile>
      <anchor>af9a0b560b9715d0e235eb9ae2838c9c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>nullTrafficChannel</name>
      <anchorfile>struct_i_s_p_h_e_n_c___in_args.html</anchorfile>
      <anchor>ac97de35c9a329850ada08e3afb1859f1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Obj</name>
    <filename>struct_i_s_p_h_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct ISPHENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_s_p_h_e_n_c___obj.html</anchorfile>
      <anchor>a5b3a8200c044373c19a3465b2a809274</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_OutArgs</name>
    <filename>struct_i_s_p_h_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>adf03c48d4a0ee962eacbff1c8ebc53fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>ae5ba034f9c0748545bf8674a7d285a7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>ab55c2dc506493a6a6860e075e52e8158</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outbufferSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___out_args.html</anchorfile>
      <anchor>a6edfb6b938404329a60626afc140e5ae</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Params</name>
    <filename>struct_i_s_p_h_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>a1eeaa38d0dd3be8f8b98002d35494395</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>acb6c0b813aead1aaab8090e9efff8be6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>compandingLaw</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>ae347c74c98a906f83b5a2c005f0f7b6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>packingType</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>aeafe6470d58388f75605a4b2a9ee3353</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadSelection</name>
      <anchorfile>struct_i_s_p_h_e_n_c___params.html</anchorfile>
      <anchor>ada2463e8eff933b2afc2b3a5ba181dde</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ISPHENC_Status</name>
    <filename>struct_i_s_p_h_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a9fe7c098724d9e48869d8cf1c5835058</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a3484a924fe8912812cf33546307516f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSize</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>af4f194cea891f8a5ac5ca9bd59d80058</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>abcef129c023f16336325924b70837f8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>ad69484eb3965162bd70c5c387c1649fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>vadFlag</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a10c25a825c2aeac37e7cbc94fc50d4bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>noiseSuppressionMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>aae2940bea7804c160bd687b9484bac51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>ttyTddMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a60445311e7c3c938ee4329b30addf124</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dtmfMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a21ae87e405581a1f2f3f0f1607417c3f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataTransmit</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a1399d6462179fd0d0aab6bc132444d38</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>homingMode</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a8c12a4ec0aef606445e7eb8b978efc15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_s_p_h_e_n_c___status.html</anchorfile>
      <anchor>a77477c93c7ae260c00212d50d98700c1</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_DynamicParams</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___dynamic_params.html</anchorfile>
      <anchor>a15355c4f8e6d2afadf99bda670980e62</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Fxns</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>a8427e1827bd68ef315a8787b91e50597</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>a4fe46a93d02d5ae1b5aeab84e8cf69a9</anchor>
      <arglist>)(IUNIVERSAL_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs, IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___fxns.html</anchorfile>
      <anchor>ab32eb3ab35b9fa34c9777c68d0b19f2b</anchor>
      <arglist>)(IUNIVERSAL_Handle handle, IUNIVERSAL_Cmd id, IUNIVERSAL_DynamicParams *params, IUNIVERSAL_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_InArgs</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___in_args.html</anchorfile>
      <anchor>af9be414dfa950c062a3583962f0267fc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Obj</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___obj.html</filename>
    <member kind="variable">
      <type>struct IUNIVERSAL_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___obj.html</anchorfile>
      <anchor>afb8fb7ade7c834512e353dd2aabb3590</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_OutArgs</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</anchorfile>
      <anchor>a3901f8ee5a120892ccca1c686f137d77</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___out_args.html</anchorfile>
      <anchor>a3c9565d7505e4f1124fa1bdd7dfb2f61</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Params</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___params.html</anchorfile>
      <anchor>ad1dc428353fb7a3a3be6d8925a9e2f16</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IUNIVERSAL_Status</name>
    <filename>struct_i_u_n_i_v_e_r_s_a_l___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>a94a07151dc36836a90c27943da2e6548</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>a942ebb5d34f7c52fdfcc854b8c6dbf2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_BufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_u_n_i_v_e_r_s_a_l___status.html</anchorfile>
      <anchor>abb4cd323acf4504cb16f0e7c0f301ecb</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_DynamicParams</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a89a472b058a47b48bf35f9d630b2eb8b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_Grid *</type>
      <name>grid</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a9a1c3eda1f8954941e6baf1481c5e3d4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>ad86e3a05938f2085187c6e2d2c265000</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_Rule</type>
      <name>rule</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___dynamic_params.html</anchorfile>
      <anchor>a9f6ff5f1a8ba77b1bfc23e75e991ded4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Fxns</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>ae78c7ef8aee125ed17a9e9846832f4f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>a697152bc6e993db00d13da49ce02df46</anchor>
      <arglist>)(IVIDANALYTICS_Handle handle, XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs, IVIDANALYTICS_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___fxns.html</anchorfile>
      <anchor>ad944512b2eae910d991086e1279ab8d5</anchor>
      <arglist>)(IVIDANALYTICS_Handle handle, IVIDANALYTICS_Cmd id, IVIDANALYTICS_DynamicParams *params, IVIDANALYTICS_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Grid</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>blockHeight</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>aadad9de1da8bc5f7a83c7efda589bc4c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>blockWidth</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a2653d8f67279b20e05f0b228981acaa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBlockHorizontal</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a8943afaeff1a3034ec8ea885979850cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBlockVertical</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a9463008dad159614786f625342f62299</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>enableMaskArray</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___grid.html</anchorfile>
      <anchor>a22d4103ed181b76db5b2a71ecf29825a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_InArgs</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</anchorfile>
      <anchor>a4139d117f5a65a36aa44d07bedbcf8af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___in_args.html</anchorfile>
      <anchor>a6ebd0affa3fb133be773deb53004be35</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Obj</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDANALYTICS_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___obj.html</anchorfile>
      <anchor>a818a9697131a5a07e102c61ed6103be2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_OutArgs</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>aa28507409a7754351df49a0584399767</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numTargets</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a14f86950466cfb603ed8cc828bd3f4a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Rect</type>
      <name>targets</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>ab93f3d95de67e25a7febf41a3dc19bc1</anchor>
      <arglist>[128]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numEvents</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a58a2b2a64e196119da2a1299173c6b2d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>eventId</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>ad78c6da1b3a6b1fd1a869cd29bc3dd60</anchor>
      <arglist>[128]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>acec206bd09ad8acbcc6842f4832d978e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Date</type>
      <name>date</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___out_args.html</anchorfile>
      <anchor>a883c5d7eb424f36cc54f4a7f75a1621c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Params</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a5836dcd5adf13b19001fb22393d89575</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ad337a654a3fd847395443390aa712f94</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a03bf452b002c12bcc44b2301975f0159</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ab6264d6f76a9ad2917b468a4f97258d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a980c99733f0208bc582d5819ed7e1933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>ad9e76064d1d91da019ec118c22edf902</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxRules</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___params.html</anchorfile>
      <anchor>a9eac89ed14d607b8b8b8c42746ece5f5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Rule</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a973da95662eb1b24ccd59eacf6e5ba7e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>id</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>adba91d965b0ff28788736df77016b8be</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_ObjectType</type>
      <name>objectType</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a2baa2a52ff057f7033356631b60f3719</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDANALYTICS_ActionType</type>
      <name>actionType</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___rule.html</anchorfile>
      <anchor>a865a0736f761a0b2ad3de3ad36956896</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDANALYTICS_Status</name>
    <filename>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>aef5c85f56b6491b34c7c3a7668765bb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>a34b4b953d61ac2abba683989c434b709</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_BufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>acbf73996a05f3a1835732c63d3c3c8d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>ade1e749887cf799d722930085f393cb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>viewState</name>
      <anchorfile>struct_i_v_i_d_a_n_a_l_y_t_i_c_s___status.html</anchorfile>
      <anchor>aea3e08dce00a80d491939e5a82997877</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_CodecClassConfig</name>
    <filename>struct_i_v_i_d_d_e_c1___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___codec_class_config.html</anchorfile>
      <anchor>aec10436d4546e1ca87ca7867b3585766</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___codec_class_config.html</anchorfile>
      <anchor>a1f8b233e088f2f307f1b23c86f38f226</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>acfe23316a964cabf5f2803ebca48130b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aeba527b40a39cbf8ab2d1cf55b6e0d3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>aa914dbaa8ccd4be77444e48321a2b74f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>ae75efcb3647729a7cbfc053137c0d4ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameOrder</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a97415f8d6295264ccfb297a2c3e7fa1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>newFrameFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a15905a53f770cac2d89aa014996d8c12</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___dynamic_params.html</anchorfile>
      <anchor>a1585382a02fb971aa5030a85586e2a32</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a277bba41de7d779c3f6d4629a0530a86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>aeb14b43b7212ac2de116381f5b07b1d4</anchor>
      <arglist>)(IVIDDEC1_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC1_InArgs *inArgs, IVIDDEC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___fxns.html</anchorfile>
      <anchor>a907ccbcc0221e6cf27c6a6d9ac08719b</anchor>
      <arglist>)(IVIDDEC1_Handle handle, IVIDDEC1_Cmd id, IVIDDEC1_DynamicParams *params, IVIDDEC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a220a48292999de7a753b53cb38c201dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>aa9e5c1ef5e0e5cad7deccc27e3f4f8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___in_args.html</anchorfile>
      <anchor>a15a674a4a16aac9c5016ba6eceda0026</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Obj</name>
    <filename>struct_i_v_i_d_d_e_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___obj.html</anchorfile>
      <anchor>a1cbed5bb6a1174539b8e06afe216b739</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a57bf5f028cef1b3104daf1d204434389</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a036474c89354f0b5b281ca144769bff0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a3b4d91aa8233cc496603a291a0c309f2</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>decodedBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a9b0fbaf05d3941fdb7a384e55704b21d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>ae6a4d7486136be164ce7ac898dcb73cb</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputMbDataID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a894cb60736b6b6ace11736bf0c060fe6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>mbDataBuf</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a0e063681f3c945bf22642c2b46c57f0f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a908c3ae1727f4b2307893ab51d42240a</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___out_args.html</anchorfile>
      <anchor>a2814bb51f173cb8ea092e2a512bdb8e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Params</name>
    <filename>struct_i_v_i_d_d_e_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a601096b5c6de01527a2ef5d0020719e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>ae1392ad3e68fb20d03da126a6c02d941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a803208ae11e51ea7afa70c4612c4b515</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a76ab8c9e7b93549a78b3f570a4bbfe82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a499b80580198e47aaa527c7fbef74730</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>a89108ef2f6456fc160468cdb97aea779</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___params.html</anchorfile>
      <anchor>ae8e32f2729f945c4086b45b389e6a71b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC1_Status</name>
    <filename>struct_i_v_i_d_d_e_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>ac4e76fb6d3d81df993f40a4040debeae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a226a2e4def4e023df187378384d2950b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a6c9e519948896577c29071e9ee3e8dd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a3c288f74c6f5773b946414eec8434df8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a72686d6a7606abb98a5c35a8e14ce053</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a908fa7a6e55bd3a38361e26c5e410faf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>a02334a7d28900fafe2ab02a2689a0cdc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>aaf3360bf85d0d4b8ccf0e868056a03e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>ac0e652666b3961bdc0201292ff2eb8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c1___status.html</anchorfile>
      <anchor>afe9bb65d9adb45bd57129e1cd9352367</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_CodecClassConfig</name>
    <filename>struct_i_v_i_d_d_e_c2___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___codec_class_config.html</anchorfile>
      <anchor>a987a36806b34cceb60c10cf72a76ad4c</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___codec_class_config.html</anchorfile>
      <anchor>a8404b647f4fcdaa94eb75b90e6a8c9a2</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c2___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>ac57ff901de30b99b9aa701fb0f330365</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>abea5bae5ff70e10a2d7010f9bda4d697</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a858643bd8ae939383b1566a57d38deeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a2981f5f0fb15a6f52bb29a4e85c0eb35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameOrder</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a03b80fd9ba446f1e5001e9ea9e500719</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>newFrameFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>aab05384e3ca3e7ae577b7feffad8b46d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___dynamic_params.html</anchorfile>
      <anchor>a645451aa3f5781816b7d850a4a0f1d80</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>a51d7618bc466b06f8c8c53bf910cacaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>a4ab91427d87c22d67136c65d848de2cf</anchor>
      <arglist>)(IVIDDEC2_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___fxns.html</anchorfile>
      <anchor>aff1ed678af0e3c7794920c5948733922</anchor>
      <arglist>)(IVIDDEC2_Handle handle, IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c2___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>aabeef7351fcd66648100d115723118c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>a061e6d40fc11ea2c9174c20ca4a01da0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___in_args.html</anchorfile>
      <anchor>a6dce78fe6188b7ee5f6f1ca75986f364</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___obj.html</anchorfile>
      <anchor>a1105edcc8ba848020ed15e7414e40766</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c2___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a46b3e25df2e65f7f80a5c21eec02ad3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>aa67374f1e59de1711f8203995643f989</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>ab1eb379f6d362275660110a30094574e</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>decodedBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a08eee7bf1ab385b15753c9b533c9ed1c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a2ccb366f52e56f40e6c9daf7907bf1c3</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputMbDataID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a15e0061a4df48edeb0f32202da60c071</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>mbDataBuf</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a8ce0694a291539fd42702f1f41fb859c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>freeBufID</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>ab82f6aa7b2be10068fc9ac811c7691da</anchor>
      <arglist>[20]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___out_args.html</anchorfile>
      <anchor>a1aaf58c88d9ddfad32419d2e6fd51447</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Params</name>
    <filename>struct_i_v_i_d_d_e_c2___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>a45489c314fccd6caecaf413141ebdaf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>a0d61886b3e936242be35a9f8b8869872</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>afb23d618cd7c1651be31d911abc90465</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>af492673482410574e9bc7851e265267f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ab0df257678abb1d57a16c89207385240</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ac68e5f9651f085c171a974890da3350d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___params.html</anchorfile>
      <anchor>ace5541457fd9ecf4ec3a196222090f83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2_Status</name>
    <filename>struct_i_v_i_d_d_e_c2___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a81c8b25dfc840080ea8e8633e1f161b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a259d22a5829769e697b986bc4b8ee7cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>abb374cb803cf489492ef6f45c0a3d29f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxNumDisplayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a8fa9d26c6e4b19492b509b4be33735f6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>abab82bc0d1552fe43a3f8db08262bd58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a8b35ac68f8e49ab93c50f818398714cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a3e4c0a0dc0d49ae4aff5321b037ccd07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a6737984a1ebdc67d112840e6424ccdcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>a502ea67283d50ab69057f487ba92a33f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>aad298369668b4cafafe33f0d5adf817d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c2___status.html</anchorfile>
      <anchor>ad6c769ede28a7e7a6724ea86da1e20d2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2BACK_CodecClassConfig</name>
    <filename>struct_i_v_i_d_d_e_c2_b_a_c_k___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___codec_class_config.html</anchorfile>
      <anchor>a2a974762f8deb4cbff6fb5f0e4e7dfa7</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___codec_class_config.html</anchorfile>
      <anchor>a569305d47e32f6b4bd0533438ea59eab</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageIntermediateBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___codec_class_config.html</anchorfile>
      <anchor>acf961246e8ca6e9b4f1c96cde20240d9</anchor>
      <arglist>[32]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2BACK_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>a24301868fe755edc445f3b19d6387614</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>abee1d2e9a4b63e97cfef3dcea6c8be70</anchor>
      <arglist>)(IVIDDEC2BACK_Handle handle, XDM_Context *context, IVIDDEC2_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___fxns.html</anchorfile>
      <anchor>a40034aadeb676ad32f9be5470bb5d49b</anchor>
      <arglist>)(IVIDDEC2BACK_Handle handle, XDM_Context *context, IVIDDEC2_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2BACK_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2_b_a_c_k___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2BACK_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_b_a_c_k___obj.html</anchorfile>
      <anchor>a73e45c9876cb548abdb45d1d577c1fc2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>a1da0af3f11e9d2f24b6aa309d7bdbee9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>afe05e338773c1ad9f0ebef9297a3d1dd</anchor>
      <arglist>)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_InArgs *inArgs, XDM_Context *context, IVIDDEC2FRONT_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___fxns.html</anchorfile>
      <anchor>ab41b180cea576791103366f0b516f620</anchor>
      <arglist>)(IVIDDEC2FRONT_Handle handle, IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *params, XDM_Context *context, IVIDDEC2FRONT_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Obj</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC2FRONT_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___obj.html</anchorfile>
      <anchor>a21a530d43b07993973e50d16a8a5dc7f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>abc4a4d10e3c660d2f4b0aa2ea4214918</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>a609a5deafeeb993df1fe35181796297f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___out_args.html</anchorfile>
      <anchor>ac1c49e75c61c69bb5fdc3c051760af83</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC2FRONT_Status</name>
    <filename>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</filename>
    <member kind="variable">
      <type>XDM_ContextInfo</type>
      <name>contextInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a1838863a9212bc08aa8f1af036dbde7d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>nextPartRequiredFlag</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a6b4b87950cf2a84fb1fd62136f96abc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>partialExtendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>a2e3560140b3489c4b0ccf5a472591a15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDDEC2_Status</type>
      <name>fullStatus</name>
      <anchorfile>struct_i_v_i_d_d_e_c2_f_r_o_n_t___status.html</anchorfile>
      <anchor>aeb46aad479a78d7f6de03aa7a81419bc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_CodecClassConfig</name>
    <filename>struct_i_v_i_d_d_e_c___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c___codec_class_config.html</anchorfile>
      <anchor>acf35f3ad3b0377d179fc934ce2b9f27e</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c___codec_class_config.html</anchorfile>
      <anchor>ad5b4270f5447519be90a55438cebb271</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageDisplayBufsCache</name>
      <anchorfile>struct_i_v_i_d_d_e_c___codec_class_config.html</anchorfile>
      <anchor>af753338c6a40b2631397a20108a843d5</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_DynamicParams</name>
    <filename>struct_i_v_i_d_d_e_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a724d728955f5ff98a352184f302e5c10</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodeHeader</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a52482680b2bbf9c6e1d3853e229fe117</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>displayWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>aab0602030993aaab21f3942b4e6e94cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipMode</name>
      <anchorfile>struct_i_v_i_d_d_e_c___dynamic_params.html</anchorfile>
      <anchor>a60f87b60ed218e4d55e6cd8bd4718095</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Fxns</name>
    <filename>struct_i_v_i_d_d_e_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>a04451418eb8c2e22322942fb38574cb9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>aafdaab50710b66ee2104d6e1d880a465</anchor>
      <arglist>)(IVIDDEC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC_InArgs *inArgs, IVIDDEC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_d_e_c___fxns.html</anchorfile>
      <anchor>af1b9b9ead4248c6423841c503f3c0241</anchor>
      <arglist>)(IVIDDEC_Handle handle, IVIDDEC_Cmd id, IVIDDEC_DynamicParams *params, IVIDDEC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_InArgs</name>
    <filename>struct_i_v_i_d_d_e_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>a004ff9f5a6272b79b6b6b3dda49b217e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>a8feea5ef537f4e573d7f23554574f3da</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c___in_args.html</anchorfile>
      <anchor>ab9faa778dc3c1a42a1479ca5968becbf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Obj</name>
    <filename>struct_i_v_i_d_d_e_c___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDDEC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_d_e_c___obj.html</anchorfile>
      <anchor>aef1a7f4a14b3af6b518bf5d4f9e6f026</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_OutArgs</name>
    <filename>struct_i_v_i_d_d_e_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>add17e78667df29acfc52f01822e1583b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>afb2c2ed91ffcee062dd75b6a7d59baf5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesConsumed</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a8c8dad1d10afa49ee7090beaa9189361</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedFrameType</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a47d05e2ae2e85e3203882e37a16feeb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>ae926f3d3ef8ee7ab71cf82db718bdb7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO_BufDesc</type>
      <name>displayBufs</name>
      <anchorfile>struct_i_v_i_d_d_e_c___out_args.html</anchorfile>
      <anchor>a1b92e3bc402ee4b64164d244628a7040</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Params</name>
    <filename>struct_i_v_i_d_d_e_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>aa4bf340158b515f6ea5e54f7973dfc83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a4b9fa2e0c94c60af4adb95c98e545bb1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>aa7cb3c68c69b29a7da94c30083ead6b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a1c578cd3ca486b35919d9c09bd0a9af7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>ac5306a39305dc3eaee2779303207424e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a09ef5e0e092f4e2fdb29bb96eada7c3e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c___params.html</anchorfile>
      <anchor>a500e3b69bc7207b1b4518f8e10e5baa8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDDEC_Status</name>
    <filename>struct_i_v_i_d_d_e_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a749fe221b3a9a9f4e389e5285cdf2653</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>af9734920ddf82abd74ea1e86a7cebf40</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>aea46a001b1af8efa60b5eabea9e04e19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a1cd8f6470f8aa60ed2a608d0eb8bdbbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>ac44eec0c38b9376bf57c40968e63eaeb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitRate</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>abbb37318036241450b81452584d52734</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a0f8379a42340c6a1336025f6fd0d0757</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>adda6498f4da63268c0a8f2c06e2d8ee8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_d_e_c___status.html</anchorfile>
      <anchor>a3973152cbffcb657d1e1117cad17b2c9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_DynamicParams</name>
    <filename>struct_i_v_i_d_e_n_c1___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a489c343510f1fa50f84055e4b7045329</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae93a29e557c5d61180159b9c11c0c1d2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ac985fdf2b369f26596edef125ece3be5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>refFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a80ce9bb1e2feb81eeddf0d5d5293ee43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aa9a41d61a27f63f7bdf011636f9371c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ad970e1d843d1a76e93999fdafb7fc68a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>ae87fe97fc61de6ce3ea4c064b8e79b6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a115309d80e5ee49ad12fd2b27d522f09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>aedf2f59085908e721d28ec190d9ce616</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceFrame</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a68e26f9b591fb6a8c65aee114d7e8d18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>interFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>a173bb3a21e19964fe0af27ff30e191de</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbDataFlag</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___dynamic_params.html</anchorfile>
      <anchor>acf24d69c70907fcb19a8f38407b06daa</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Fxns</name>
    <filename>struct_i_v_i_d_e_n_c1___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>adc0a1d06f7ae43793ce895562652ec98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>aa4247d185bc5a015147cfd42f516111d</anchor>
      <arglist>)(IVIDENC1_Handle handle, IVIDEO1_BufDescIn *inBufs, XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___fxns.html</anchorfile>
      <anchor>a2ed409eed307f42fe7e3aaedbf081f07</anchor>
      <arglist>)(IVIDENC1_Handle handle, IVIDENC1_Cmd id, IVIDENC1_DynamicParams *params, IVIDENC1_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_InArgs</name>
    <filename>struct_i_v_i_d_e_n_c1___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>adad9db74820009e7a1621d06e0347ec2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a585d2442323056cdd61f66e196d0658b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>topFieldFirstFlag</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___in_args.html</anchorfile>
      <anchor>a5d4dc8e55e03eb69f035fd7cd26d0c4e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_MbData</name>
    <filename>struct_i_v_i_d_e_n_c1___mb_data.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mbMode</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>ad5f71db4894b7c2f4fa27cc1cffaa0af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>QP</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>a67f67068f048a8a612c3fe18cd769432</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mvFwdXY</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>af081a2b06b14cca3538b4c76633bc8b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>mvBwdXY</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___mb_data.html</anchorfile>
      <anchor>ac49f52a1b362799b5e4205aad72d1555</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Obj</name>
    <filename>struct_i_v_i_d_e_n_c1___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDENC1_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___obj.html</anchorfile>
      <anchor>a48243d06fe2e480272019fdcf3f8cce2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_OutArgs</name>
    <filename>struct_i_v_i_d_e_n_c1___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a3d278124523dc17b36624e7031aefe25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>ac828cb5ed028e9f244d7497db79ce885</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5ace229c1e049582f74913572c9b920d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedFrameType</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5a4e85d4f0a27de4672aa7aa40553034</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkip</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>af5881d8a6d39e1feffab343d2609dc25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a5f5e04e01c1074223f9ab973bb0dfcb4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>encodedBuf</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a084284ba0a81fcdd501a1d5c7114cffa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO1_BufDesc</type>
      <name>reconBufs</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___out_args.html</anchorfile>
      <anchor>a2a8e9941e9f0130bf8ee0b6cb98d655e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Params</name>
    <filename>struct_i_v_i_d_e_n_c1___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a5ee2d4064a258de5333aefff7596e354</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>afc35f26f61dbd811d24bc3f79fdf8360</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a535c201ff37d0dfa730066529ad37f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac412b8143362fd31738fef01a3186a27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a2aedfe4ebbbba9fff8584eba862038e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a836ce8d8ac908c3331ab23cd41169ccb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>aadca2c4e03720839c307b9cc5ef6725c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac6bcb7e34fa71e7250bd806b9a3d3842</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>ac2c24101728082e7832a1e2bad0a92ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a5b29b3bbe4909783f2b9842f28ff4d99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a0f8ae7b2cbc0465c773186ef1fcad7bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>reconChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___params.html</anchorfile>
      <anchor>a0d38c9a7be268b6ea4fafd8349266bf4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC1_Status</name>
    <filename>struct_i_v_i_d_e_n_c1___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>abf7188f0a82eecbd8f5cf681420dae15</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>aa4d8b297809354dcd04637def44dcd75</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>ae8549df00ae60654319529046e88f35e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_e_n_c1___status.html</anchorfile>
      <anchor>af759092bb3361da6d7e77505e41c4f71</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_CodecClassConfig</name>
    <filename>struct_i_v_i_d_e_n_c___codec_class_config.html</filename>
    <member kind="variable">
      <type>Bool</type>
      <name>manageInBufsCache</name>
      <anchorfile>struct_i_v_i_d_e_n_c___codec_class_config.html</anchorfile>
      <anchor>ada79a0792b9453a2b985144885a46c74</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageOutBufsCache</name>
      <anchorfile>struct_i_v_i_d_e_n_c___codec_class_config.html</anchorfile>
      <anchor>ab87a97ce537461f070b3243abfca3222</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>Bool</type>
      <name>manageReconBufsCache</name>
      <anchorfile>struct_i_v_i_d_e_n_c___codec_class_config.html</anchorfile>
      <anchor>a1b4a91b56f0b8ea50f307a69797d73f6</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_DynamicParams</name>
    <filename>struct_i_v_i_d_e_n_c___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a98eba6b02ca906bfa9d5cbe083540d98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>aa02d428378d4a56c033113bdca825ff6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ad200571290f2cafa1e612e1d396be378</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>refFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5b23cf9832abdad3a7ea5f1181961f61</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a12d0d0b205549f63da4bb0cc57acd162</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5409bcb2aca77a54f0b58d91c145c9b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a5f05ef1fa666e0ca5f72a06b0c44c91e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>generateHeader</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>ab66404bf763f5fec96103290666f9df7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>captureWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a80bbc137ed001f8d3b164420c28f8a17</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceIFrame</name>
      <anchorfile>struct_i_v_i_d_e_n_c___dynamic_params.html</anchorfile>
      <anchor>a67945462578816ca2be1b56c58ff48c2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Fxns</name>
    <filename>struct_i_v_i_d_e_n_c___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>ac47a41d81910244f6ab29f526aa52e5b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>a0d97541aab401b55c7f0be829a506c7c</anchor>
      <arglist>)(IVIDENC_Handle handle, XDM_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDENC_InArgs *inArgs, IVIDENC_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_e_n_c___fxns.html</anchorfile>
      <anchor>ad99a6d6ebe14b818a63f179665af98bd</anchor>
      <arglist>)(IVIDENC_Handle handle, IVIDENC_Cmd id, IVIDENC_DynamicParams *params, IVIDENC_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_InArgs</name>
    <filename>struct_i_v_i_d_e_n_c___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___in_args.html</anchorfile>
      <anchor>a3299ddd3111ebd0fdc00dd72beeff3ec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Obj</name>
    <filename>struct_i_v_i_d_e_n_c___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDENC_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_e_n_c___obj.html</anchorfile>
      <anchor>a8ef6f8f0b78b70f1460f2c35d540b14e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_OutArgs</name>
    <filename>struct_i_v_i_d_e_n_c___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>afd2cac7f08ba6278452494e4e074398d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a963f9c1107899eb8e4f2ada9e3a87dcc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bytesGenerated</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a4a9eb44e2d428084879ef1388a8891a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedFrameType</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>aeca9f172c78c0b54cfcbf7d894abfdb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkip</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a295ded297386d8eee50dce16848a989a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>IVIDEO_BufDesc</type>
      <name>reconBufs</name>
      <anchorfile>struct_i_v_i_d_e_n_c___out_args.html</anchorfile>
      <anchor>a602f9a889f7e7d463cde193c81c22c4c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Params</name>
    <filename>struct_i_v_i_d_e_n_c___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>affe3f89977ba6a7919247f9193e002a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodingPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a16a1a6439db8d384752cc2b14d68fadf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControlPreset</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a0a14471207fd0da5611e06e4e6cd8c1e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeight</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>affa8e31a39d1024ebfac440f3d1b90ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidth</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a73fd4b94c772bed243cef7043c1c989a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a995486cb7842251b9c4ba319d9f7e8bd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRate</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a598111fa7941cfab3a3a66f23510e82f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>aaeb2aea677340d7a2d3bc6c4f5f24d37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxInterFrameInterval</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a1655f549fac120285abd37e0d10d22f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputChromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a43d8db5ae1321f4c162a6c2ef3ed98fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputContentType</name>
      <anchorfile>struct_i_v_i_d_e_n_c___params.html</anchorfile>
      <anchor>a831c15d0ee24f5bac987867e0be5a83e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDENC_Status</name>
    <filename>struct_i_v_i_d_e_n_c___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a9cf63fd66da1ba66952919a10d4ea043</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a1a7bc44c3a862ec9c31588d015bd9be3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_e_n_c___status.html</anchorfile>
      <anchor>a4b60d4421ae14fa616762a0619cc1fa0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO1_BufDesc</name>
    <filename>struct_i_v_i_d_e_o1___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a563276f15eadb93140fcc867bd83fbee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameWidth</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a7171c1f434d206bd47bff61ee1ee5ff8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameHeight</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a212f9f5576c65b04f8f469fd4ce722b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>framePitch</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>aea457ad964dcfa2f084cdc79e4d59453</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>bufDesc</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>afc3e2ae20b9c0a073a4c1d6d89248f51</anchor>
      <arglist>[3]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>ac1287f7d9d947895d000133cd6361c05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameType</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a23b93700f305277b0be3fef34a7c79f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>topFieldFirstFlag</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a0e77f5f253f8a17d41cb35a3dff1866a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFirstFieldFlag</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a5ba727127a0a4e282de30f7d0cb632b9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameStatus</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>ab3363491ad62027696388804cc313f3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>repeatFrame</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a0715059571ff444e1fd8fde93cef1c4f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>contentType</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a33e4295bca640fd6550d557aa4a1741a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>chromaFormat</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc.html</anchorfile>
      <anchor>a057facc459db9fecda02ed1be138f4f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO1_BufDescIn</name>
    <filename>struct_i_v_i_d_e_o1___buf_desc_in.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a4dfd6b4c21298ac7562a5e062bd6d69e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameWidth</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a7723b31ade67afbe6036e9215dc9f126</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameHeight</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a46f0d86c006c987569e4d9c730f52fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>framePitch</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>a7046bea1dcc1731ede9981d1a1515528</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>bufDesc</name>
      <anchorfile>struct_i_v_i_d_e_o1___buf_desc_in.html</anchorfile>
      <anchor>abc19804f6895c76a09f40f9e71001d38</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDEO_BufDesc</name>
    <filename>struct_i_v_i_d_e_o___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a4b573a1cb65d666485d2a03ed17c9e95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>width</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a6b6726ea8e06f258d59c649fbf985ce7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>bufs</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a51ee0b81967a3306d3e091fbc81a38a6</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSizes</name>
      <anchorfile>struct_i_v_i_d_e_o___buf_desc.html</anchorfile>
      <anchor>a925dd5695afe66711bdc0c3ada614fe2</anchor>
      <arglist>[XDM_MAX_IO_BUFFERS]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_DynamicParams</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a98cc0ea4d936f8c972ddfc84bb225ae5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>readHeaderOnlyFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aa951419bb5af977888b92936087ebac9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputResolutionFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a95260da3ba755de635b1950e52d9b67b</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputHeight</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a03b473acd5cb95aeab754a7bcfc6eb03</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputWidth</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a279a4ccdff85f35308292d201e5666cd</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputFrameRateFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aa443d68d2d427f97f731a29be6df2705</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a86851c98010bcfe6e998841a8cb95b51</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputFrameRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a52d8329cfee67f5d18d3720b6b0edc62</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>targetBitRate</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a8bb8bfabd89d507e736b1a6b709b2e26</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>rateControl</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a97f553d1d58d3c448120e074fcd71f13</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>keepInputGOPFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a29e3ade6cf84c1e854fe107ca0132366</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>intraFrameInterval</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>aec20f697b5a609fa0bc964121ce97b2d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>interFrameInterval</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a24900a188335c7dddac1d97bd54ae537</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>forceFrame</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a53277e5a3b166083d1acea344cb0178d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>frameSkipTranscodeFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___dynamic_params.html</anchorfile>
      <anchor>a56851a58acea8a5a5f23e1cedab89fdc</anchor>
      <arglist>[2]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Fxns</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</filename>
    <member kind="variable">
      <type>IALG_Fxns</type>
      <name>ialg</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>a00a8d6fcd816e541445cbffb7d572d3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>process</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>ae1f9478ee3ed195162e901e41ef4bafc</anchor>
      <arglist>)(IVIDTRANSCODE_Handle handle, XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs, IVIDTRANSCODE_OutArgs *outArgs)</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32(*</type>
      <name>control</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___fxns.html</anchorfile>
      <anchor>abd9deef58e96781eb52b91b4f42dce34</anchor>
      <arglist>)(IVIDTRANSCODE_Handle handle, IVIDTRANSCODE_Cmd id, IVIDTRANSCODE_DynamicParams *params, IVIDTRANSCODE_Status *status)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_InArgs</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>a369131f165301ff566f3396265bb89fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBytes</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>af9e5ddb4d5b77a1c6641e685c350a61a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputID</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___in_args.html</anchorfile>
      <anchor>a6eb9c1f6eec0cd42a7437915089c2112</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Obj</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___obj.html</filename>
    <member kind="variable">
      <type>struct IVIDTRANSCODE_Fxns *</type>
      <name>fxns</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___obj.html</anchorfile>
      <anchor>aa26c81e61c53a7eb397f6123a5d64d28</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_OutArgs</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a46367326d4ff223657cd42ae7258114a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>ad552ac49e07818ada5b1f9704401dc54</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitsConsumed</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a8ba51d9a51c5c47005c80d186d850a30</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bitsGenerated</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a72ebef4f6a96d7362faf89764c64312d</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedPictureType</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>adba4f0481ff4679f34ec661f6f8e45bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedPictureStructure</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a0941d9a0187a7dd27ba8ad367727b3b2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedPictureType</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a30574aaf1af1060d0f4f19dae6a2ae5e</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>encodedPictureStructure</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a077dcad3cf77db21ced1e679a19792b2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedHeight</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a8d0121348bdc359d42d4909e5e3eb793</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>decodedWidth</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a2b71370ceeda0bf2e4639b5d81ec3ea8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outputID</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a5cf133cb2fd5c39b96f0684b4c3e82f4</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>inputFrameSkipTranscodeFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a550034f1df2ec83a894cbefc1718d7e0</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>encodedBuf</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a6c4eaab6595ae3a1c8fba7a42fc0a7f2</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>outBufsInUseFlag</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___out_args.html</anchorfile>
      <anchor>a94bf3a6788838c68e5c7dbe57cbb8a44</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Params</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a79d39b07d4a8f0818bdd00b97f2684cc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutputStreams</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a940c0bbd6b0992814a6a2f37742a6b6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>formatInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a130380061ebff67a68c36f5246b07d9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>formatOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a28d64e676cb384be4889d51ad4ff8839</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeightInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>ae98568eef86ddd44e877f5b5e2cd3ead</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidthInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a6fe80a4a33170b65865ecae1d4cc5819</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRateInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a79834d1d0fb5282e84cdb184e284edd2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRateInput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a9c4692f8f6f661904f404ba9049f492b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxHeightOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>afba039a90e6d8b95d8100c0b01300b70</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxWidthOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a902f9dd976de613b662e13659682de6a</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxFrameRateOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>ae6283acffcb489920bc4e945655c9c40</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>maxBitRateOutput</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>af3369094666dd2eccf50de897cb53e60</anchor>
      <arglist>[2]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dataEndianness</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___params.html</anchorfile>
      <anchor>a9bc4dc747100a365d8a6180e128108ff</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>IVIDTRANSCODE_Status</name>
    <filename>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>size</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>ac25ec58daf95e011c44401d55891adbc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>extendedError</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>a3f577b4e0f0f1b128b46d4d94c7c4d05</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>data</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>a5f558a163c0252362f67b5f8d64cf120</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_AlgBufInfo</type>
      <name>bufInfo</name>
      <anchorfile>struct_i_v_i_d_t_r_a_n_s_c_o_d_e___status.html</anchorfile>
      <anchor>acf679f7bd2bdd52724e109775b700795</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>LAD_DspStatus</name>
    <filename>struct_l_a_d___dsp_status.html</filename>
    <member kind="variable">
      <type>LAD_DspState</type>
      <name>dspState</name>
      <anchorfile>struct_l_a_d___dsp_status.html</anchorfile>
      <anchor>a397bd9305ab41db663c087b380f6c014</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Char</type>
      <name>linkConfigName</name>
      <anchorfile>struct_l_a_d___dsp_status.html</anchorfile>
      <anchor>a6964ea6c025e459a8266ee49045dc393</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>numClientsStarted</name>
      <anchorfile>struct_l_a_d___dsp_status.html</anchorfile>
      <anchor>a1d8172fdd5f11854087bc9ff506232fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Char</type>
      <name>imageName</name>
      <anchorfile>struct_l_a_d___dsp_status.html</anchorfile>
      <anchor>a51024bd6ed11a25b22ce12ff888fd4f0</anchor>
      <arglist>[512]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Memory_AllocParams</name>
    <filename>struct_memory___alloc_params.html</filename>
    <member kind="variable">
      <type>Memory_type</type>
      <name>type</name>
      <anchorfile>struct_memory___alloc_params.html</anchorfile>
      <anchor>a8a9b5ea0bc3d7d01d115166b7607d0bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UInt</type>
      <name>flags</name>
      <anchorfile>struct_memory___alloc_params.html</anchorfile>
      <anchor>ab8113726ac4d721815cd6041ac236e4d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UInt</type>
      <name>align</name>
      <anchorfile>struct_memory___alloc_params.html</anchorfile>
      <anchor>aca058e7a623aabc838b3902b77d23f39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>UInt</type>
      <name>seg</name>
      <anchorfile>struct_memory___alloc_params.html</anchorfile>
      <anchor>a5db6d4d0e09922c3d878876c7ad26ed9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Server_AlgInfo</name>
    <filename>struct_server___alg_info.html</filename>
    <member kind="variable">
      <type>Int</type>
      <name>algInfoSize</name>
      <anchorfile>struct_server___alg_info.html</anchorfile>
      <anchor>a9df96f70c50f2465ad84c1d5398a125b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String</type>
      <name>name</name>
      <anchorfile>struct_server___alg_info.html</anchorfile>
      <anchor>a6ba931ccdd99c4f74f7d63dc383c55fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>String *</type>
      <name>typeTab</name>
      <anchorfile>struct_server___alg_info.html</anchorfile>
      <anchor>ad52c3dd77f3c0430d600f55eb8531587</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Server_MemStat</name>
    <filename>struct_server___mem_stat.html</filename>
    <member kind="variable">
      <type>Char</type>
      <name>name</name>
      <anchorfile>struct_server___mem_stat.html</anchorfile>
      <anchor>abdb5b45fe0620bf036e25f948f8a2164</anchor>
      <arglist>[32+1]</arglist>
    </member>
    <member kind="variable">
      <type>Uint32</type>
      <name>base</name>
      <anchorfile>struct_server___mem_stat.html</anchorfile>
      <anchor>a008bb41bc0eb1e30d1684fc7d18154dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint32</type>
      <name>size</name>
      <anchorfile>struct_server___mem_stat.html</anchorfile>
      <anchor>aa97c505c3a97b129da8d66a4218243d7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint32</type>
      <name>used</name>
      <anchorfile>struct_server___mem_stat.html</anchorfile>
      <anchor>afa0185f71e41f5b1ac2322f3f196f595</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Uint32</type>
      <name>maxBlockLen</name>
      <anchorfile>struct_server___mem_stat.html</anchorfile>
      <anchor>af03816e03b86c790bcd0ea3ce86a55ed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VISA_MsgHeader</name>
    <filename>struct_v_i_s_a___msg_header.html</filename>
    <member kind="variable">
      <type>NODE_MsgHeader</type>
      <name>header</name>
      <anchorfile>struct_v_i_s_a___msg_header.html</anchorfile>
      <anchor>a3d781e76f0b18d3699f65511aa2c28c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Int</type>
      <name>cmd</name>
      <anchorfile>struct_v_i_s_a___msg_header.html</anchorfile>
      <anchor>a6c989b8f8016b9a1d2a90fc8fc9529f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VISA_Status</type>
      <name>status</name>
      <anchorfile>struct_v_i_s_a___msg_header.html</anchorfile>
      <anchor>ad07fb3c1759d07fb38669648ab9d330c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM1_BufDesc</name>
    <filename>struct_x_d_m1___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_x_d_m1___buf_desc.html</anchorfile>
      <anchor>ace565469a1d5d01af34c086777ad0498</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>descs</name>
      <anchorfile>struct_x_d_m1___buf_desc.html</anchorfile>
      <anchor>a8d932c31ffeeb1c11f7345a30f8f0db1</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM1_SingleBufDesc</name>
    <filename>struct_x_d_m1___single_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>buf</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>acd2b309ae89361a09bf3511e45f2f8c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSize</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>a138bcbac3e40333ec1983963ba8028cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>accessMask</name>
      <anchorfile>struct_x_d_m1___single_buf_desc.html</anchorfile>
      <anchor>a9795495a0ea10e9c5f9e321b2aa3e3e6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_AlgBufInfo</name>
    <filename>struct_x_d_m___alg_buf_info.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumInBufs</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>adc9062dc88f377394cce8d084f9998af</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minNumOutBufs</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>a1c0f70a8452105b3684cc01b7f56efc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minInBufSize</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>a015d0f09a3e361fa82209fd071133b8e</anchor>
      <arglist>[16]</arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minOutBufSize</name>
      <anchorfile>struct_x_d_m___alg_buf_info.html</anchorfile>
      <anchor>ab4074aff4d3b8179e21199390682a76c</anchor>
      <arglist>[16]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_BufDesc</name>
    <filename>struct_x_d_m___buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 **</type>
      <name>bufs</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>aece1843a93b99e6c6451264208dd16ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numBufs</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>a3c4b5a0406ad1fab1aa0977de9e8e3a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32 *</type>
      <name>bufSizes</name>
      <anchorfile>struct_x_d_m___buf_desc.html</anchorfile>
      <anchor>a44b447ce14cecf3e17702c82f5ce277d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Context</name>
    <filename>struct_x_d_m___context.html</filename>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>algContext</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>ada38c0878618615e6acb50e1a1c6b9d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a9b0ebd9daf101e296d3f70301874d2b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>adf4a68410dd00a7bcbaf11b93a019492</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>numInOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>ac1d40006838339031a28d03f5fc331cf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>inBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a74044ab712df28a47157e537932a2263</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>outBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a9ee540275d6f4680e64625099893d864</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>inOutBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>a300e622b9d8a7e9ff88e42e684366863</anchor>
      <arglist>[32]</arglist>
    </member>
    <member kind="variable">
      <type>XDM1_SingleBufDesc</type>
      <name>intermediateBufs</name>
      <anchorfile>struct_x_d_m___context.html</anchorfile>
      <anchor>aa388cac43ec41696b463bd7a004f8e10</anchor>
      <arglist>[32]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_ContextInfo</name>
    <filename>struct_x_d_m___context_info.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minContextSize</name>
      <anchorfile>struct_x_d_m___context_info.html</anchorfile>
      <anchor>af6249efc3c2a1d1ea8f9031888d901a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>minIntermediateBufSizes</name>
      <anchorfile>struct_x_d_m___context_info.html</anchorfile>
      <anchor>a2060d35bda9af2ac860bda8eb7774434</anchor>
      <arglist>[32]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Date</name>
    <filename>struct_x_d_m___date.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>msecsOfDay</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a629ae642cdbad0f125be9f1f3b3b519c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>month</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a453fe75a9bcdf0892284b093bd5dde99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dayOfMonth</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a83f49e069389b965d6db9b3797ee86bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>dayOfWeek</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a351425bd2fff9f01679941b7c2ef5fde</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>year</name>
      <anchorfile>struct_x_d_m___date.html</anchorfile>
      <anchor>a4e7602f0ebd0bf5282aa61b1efb3b4ec</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Point</name>
    <filename>struct_x_d_m___point.html</filename>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>x</name>
      <anchorfile>struct_x_d_m___point.html</anchorfile>
      <anchor>a328754afc6863d3939c5823207c1724c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>y</name>
      <anchorfile>struct_x_d_m___point.html</anchorfile>
      <anchor>ae9b4eb16c8b0f76372b3ce5c219b6e14</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_Rect</name>
    <filename>struct_x_d_m___rect.html</filename>
    <member kind="variable">
      <type>XDM_Point</type>
      <name>topLeft</name>
      <anchorfile>struct_x_d_m___rect.html</anchorfile>
      <anchor>a9ddace330c4514c9282c9b48d5aad7a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDM_Point</type>
      <name>bottomRight</name>
      <anchorfile>struct_x_d_m___rect.html</anchorfile>
      <anchor>ae59a1d16898d45c5a6f8cfb3e8d3e6f2</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>XDM_SingleBufDesc</name>
    <filename>struct_x_d_m___single_buf_desc.html</filename>
    <member kind="variable">
      <type>XDAS_Int8 *</type>
      <name>buf</name>
      <anchorfile>struct_x_d_m___single_buf_desc.html</anchorfile>
      <anchor>a0205618de83e9bdf7285a6d449837d27</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>XDAS_Int32</type>
      <name>bufSize</name>
      <anchorfile>struct_x_d_m___single_buf_desc.html</anchorfile>
      <anchor>abebb7b78b54fd5ef3b3414db48245292</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/audio/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio/</path>
    <filename>dir_f007ec01408d42e8333baa23e14bfece.html</filename>
    <file>auddec.h</file>
    <file>audenc.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/audio1/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/audio1/</path>
    <filename>dir_8c6a96f369fabeaa9bd8328b22ce4101.html</filename>
    <file>auddec1.h</file>
    <file>audenc1.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/</path>
    <filename>dir_8af2a384007afa3ed36d76153cb32d40.html</filename>
    <dir>packages/ti/sdo/ce/audio/</dir>
    <dir>packages/ti/sdo/ce/audio1/</dir>
    <dir>packages/ti/sdo/ce/image/</dir>
    <dir>packages/ti/sdo/ce/image1/</dir>
    <dir>packages/ti/sdo/ce/osal/</dir>
    <dir>packages/ti/sdo/ce/speech/</dir>
    <dir>packages/ti/sdo/ce/speech1/</dir>
    <dir>packages/ti/sdo/ce/universal/</dir>
    <dir>packages/ti/sdo/ce/utils/</dir>
    <dir>packages/ti/sdo/ce/vidanalytics/</dir>
    <dir>packages/ti/sdo/ce/video/</dir>
    <dir>packages/ti/sdo/ce/video1/</dir>
    <dir>packages/ti/sdo/ce/video2/</dir>
    <dir>packages/ti/sdo/ce/vidtranscode/</dir>
    <file>CERuntime.h</file>
    <file>Engine.h</file>
    <file>Server.h</file>
    <file>visa.h</file>
  </compound>
  <compound kind="dir">
    <name>cetools/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/</path>
    <filename>dir_ff72b27bff4d7ce7a1404d3ee6d9fe91.html</filename>
    <dir>cetools/packages/</dir>
  </compound>
  <compound kind="dir">
    <name>cetools/packages/ti/xdais/dm/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/</path>
    <filename>dir_2f7a259c1b8cc18c70342da2d5db48f2.html</filename>
    <dir>cetools/packages/ti/xdais/dm/split/</dir>
    <file>iauddec.h</file>
    <file>iauddec1.h</file>
    <file>iaudenc.h</file>
    <file>iaudenc1.h</file>
    <file>iaudio.h</file>
    <file>iimgdec.h</file>
    <file>iimgdec1.h</file>
    <file>iimgenc.h</file>
    <file>iimgenc1.h</file>
    <file>ispeech.h</file>
    <file>ispeech1.h</file>
    <file>ispeech1_amr.h</file>
    <file>ispeech1_evrc.h</file>
    <file>ispeech1_g723.h</file>
    <file>ispeech1_g726.h</file>
    <file>ispeech1_pcm.h</file>
    <file>ispeech1_smv.h</file>
    <file>ispeech1_wbamr.h</file>
    <file>isphdec.h</file>
    <file>isphdec1.h</file>
    <file>isphenc.h</file>
    <file>isphenc1.h</file>
    <file>iuniversal.h</file>
    <file>ividanalytics.h</file>
    <file>ividdec.h</file>
    <file>ividdec1.h</file>
    <file>ividdec2.h</file>
    <file>ividenc.h</file>
    <file>ividenc1.h</file>
    <file>ivideo.h</file>
    <file>ividtranscode.h</file>
    <file>xdm.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/dsplink/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/dsplink/</path>
    <filename>dir_0779fae96b8848db1c8f102102aea059.html</filename>
    <dir>packages/ti/dsplink/utils/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/image/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image/</path>
    <filename>dir_f45092f750714e3042690bc0aec950ec.html</filename>
    <file>imgdec.h</file>
    <file>imgenc.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/image1/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/image1/</path>
    <filename>dir_3090b5f1b77f0ece7145095aec058de3.html</filename>
    <file>imgdec1.h</file>
    <file>imgenc1.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/dsplink/utils/ladclient/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/dsplink/utils/ladclient/</path>
    <filename>dir_856296a1ee0b923066be10db401b6de2.html</filename>
    <file>ladclient.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/osal/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/osal/</path>
    <filename>dir_b6d956bad2b5ce60710d874b0547a9c8.html</filename>
    <file>Memory.h</file>
  </compound>
  <compound kind="dir">
    <name>cetools/packages/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/</path>
    <filename>dir_c7026c914b3b543cabb7ab3c3e1c7cbc.html</filename>
    <dir>cetools/packages/ti/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/</path>
    <filename>dir_ac15fb50ef8afb56ea9466ee2634ed96.html</filename>
    <dir>packages/ti/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/</path>
    <filename>dir_f070f4d9a58b59d7df9c1d8caf31b0a7.html</filename>
    <dir>packages/ti/sdo/ce/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/speech/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech/</path>
    <filename>dir_55f5e69655c682dbc3f8f36e36619983.html</filename>
    <file>sphdec.h</file>
    <file>sphenc.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/speech1/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/speech1/</path>
    <filename>dir_2eebe1deb6c4947296d3e9cf8e93027a.html</filename>
    <file>sphdec1.h</file>
    <file>sphenc1.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/video2/split/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video2/split/</path>
    <filename>dir_87bc5b664851c6d34354f002fb6bc90f.html</filename>
    <file>split/viddec2.h</file>
  </compound>
  <compound kind="dir">
    <name>cetools/packages/ti/xdais/dm/split/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/dm/split/</path>
    <filename>dir_dc95a1669fbf039d80565ee13b4343dd.html</filename>
    <file>split/ividdec2.h</file>
  </compound>
  <compound kind="dir">
    <name>cetools/packages/ti/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/</path>
    <filename>dir_f346f875e4ad86b149ec5edb3694152d.html</filename>
    <dir>cetools/packages/ti/xdais/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/</path>
    <filename>dir_487e61e8d2ebf669b50ab44a5d2bb8c2.html</filename>
    <dir>packages/ti/dsplink/</dir>
    <dir>packages/ti/sdo/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/utils/trace/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/utils/trace/</path>
    <filename>dir_64a9580a60e01a5eb7b3abc39fad67d5.html</filename>
    <file>TraceUtil.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/universal/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/universal/</path>
    <filename>dir_62f630c66815ae94b1d2490356c7746c.html</filename>
    <file>universal.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/utils/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/utils/</path>
    <filename>dir_c6edb640a7258ab343bb31c1b0cfb2e9.html</filename>
    <dir>packages/ti/sdo/ce/utils/trace/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/dsplink/utils/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/dsplink/utils/</path>
    <filename>dir_a546316629d914010651de10ff77243d.html</filename>
    <dir>packages/ti/dsplink/utils/ladclient/</dir>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/vidanalytics/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/vidanalytics/</path>
    <filename>dir_c0ea2fa3adcfed42667138fab0b233a2.html</filename>
    <file>vidanalytics.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/video/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video/</path>
    <filename>dir_db21f1f66f1fc755e9eedc31432987d8.html</filename>
    <file>viddec.h</file>
    <file>videnc.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/video1/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video1/</path>
    <filename>dir_a8103cf3db4ae85e3c33671c0434770d.html</filename>
    <file>viddec1.h</file>
    <file>videnc1.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/video2/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/video2/</path>
    <filename>dir_f4626378ea334288428b104bb37461c6.html</filename>
    <dir>packages/ti/sdo/ce/video2/split/</dir>
    <file>viddec2.h</file>
  </compound>
  <compound kind="dir">
    <name>packages/ti/sdo/ce/vidtranscode/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/packages/ti/sdo/ce/vidtranscode/</path>
    <filename>dir_72d1dedc40122804cbc9ad9fb19ef5bc.html</filename>
    <file>vidtranscode.h</file>
  </compound>
  <compound kind="dir">
    <name>cetools/packages/ti/xdais/</name>
    <path>/db/atree/library/trees/ce/ce-r11x/src/codec_engine_2_26_02_11/cetools/packages/ti/xdais/</path>
    <filename>dir_b2a290a4e3c49d0bb766ba57ff8b9c37.html</filename>
    <dir>cetools/packages/ti/xdais/dm/</dir>
    <file>ialg.h</file>
    <file>xdas.h</file>
  </compound>
</tagfile>
