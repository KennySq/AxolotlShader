struct VertexShaderInput
{
    float3 pos : POSITION;
    float3 nor : NORMAL0;
    float2 tex : TEXCOORD0;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 nor : TEXCOORD0;
    float2 tex : TEXCOORD1;
};


cbuffer Generals : register(b3)
{
    float4x4 Projection;
    float4x4 WorldViewProjection;
};

cbuffer Generals2 : register(b4)
{
    float3x3 World;
    float4x4 OtherMat0;
    float4x4 OtherMat1;
}

PixelShaderInput VS(VertexShaderInput input)
{
    PixelShaderInput output;

    output.pos = mul(float4(input.pos, 1), WorldViewProjection);
    output.pos = mul(output.pos, OtherMat0);
    output.nor = mul(input.nor, World);
    
    output.tex = input.tex;

    return output;
}