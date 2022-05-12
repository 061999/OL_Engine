struct VSOUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

Texture2D tex;

SamplerState state;

float4 main(VSOUT vsout) : SV_TARGET
{
    return tex.Sample(state, vsout.texCoord);
}