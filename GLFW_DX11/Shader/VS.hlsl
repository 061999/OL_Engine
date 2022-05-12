struct VSOUT
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer View : register(b0)
{
    matrix perspectice;
};

cbuffer Translate : register(b1)
{
    matrix trans;
};

VSOUT main(float3 pos : POSITION, float3 texcoord : TEXCOORD)
{
    
    VSOUT vsout = { mul(mul(float4(pos, 1.0), trans), perspectice), texcoord.xy };
    return vsout;
}