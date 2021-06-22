//==========================================================================
// 2D�`��̊�b�V�F�[�_�[[Sprite2D.fx]
// author: MasyoLab
//==========================================================================

//==========================================================================
// �O���[�o���ϐ�
//==========================================================================
float4x4 Projection; // �v���W�F�N�V�����ϊ��s��
float4x4 World; // ���[���h�s��
texture Texture; // �e�N�X�`��
float uvLeft; // ��UV
float uvTop; // ��UV
float uvWidth; // �EUV
float uvHeight; // ��UV
float4 Color; // �F
bool TexFlag; // �e�N�X�`���̂���Ȃ� false:�Ȃ� true:����

//==========================================================================
// �T���v���[
//==========================================================================
sampler Sampler = sampler_state
{
    texture = <Texture>;
};

//==========================================================================
// ���͗p�\����
//==========================================================================
struct vsInput
{
    float3 pos : POSITION;
    float2 tex : TEXCOORD0;
};

//==========================================================================
// �o�͗p�\����
//==========================================================================
struct vsOutput
{
    float4 pos : POSITION;
    float2 tex : TEXCOORD0;
};

//==========================================================================
// ���_�V�F�[�_
//==========================================================================
void main(in vsInput input, out vsOutput output)
{
    output = (vsOutput) 0;
   
    output.pos = mul(float4(input.pos, 1.0f), World);
    output.pos = mul(output.pos, Projection);
    output.tex = input.tex * float2(uvWidth, uvHeight) + float2(uvLeft, uvTop);
}

//==========================================================================
// �s�N�Z���V�F�[�_
//==========================================================================
void ps2DMain(in vsOutput input, out float4 color : COLOR0)
{
    if (TexFlag)
    {
        color = tex2D(Sampler, input.tex);
        color *= Color;
    }
    else
    {
        color = Color;
    }
}

//==========================================================================
// ���C���V�F�[�_�[�̃p�b�P�[�W
//==========================================================================
technique MainShader2D
{
    pass P0
    {
        // �g�p����V�F�[�_�[��n��
        VertexShader = compile vs_3_0 main();
        PixelShader = compile ps_3_0 ps2DMain();
        
        // Effect States
        AlphaBlendEnable = true;
        SrcBlend = SRCALPHA;
        DestBlend = INVSRCALPHA;
    }
}
