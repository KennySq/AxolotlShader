struct VertexShaderInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD;
};

struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float2 tex : TEXCOORD;
};


cbuffer Generals : register(b3)
{
    float4x4 Projection;
    float4x4 WorldViewProjection;
    float4x4 View;
};

cbuffer Generals2 : register(b4)
{
    float4x4 World;
    float4x4 OtherMat0;
    float4x4 OtherMat1;
}

PixelShaderInput VS(VertexShaderInput input)
{
    PixelShaderInput output;

    output.pos = mul(float4(input.pos, 1), WorldViewProjection);
    output.pos = mul(output.pos, OtherMat0);
    output.tex = input.tex;

    return output;
}