#include "headers.h"
bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis)
{

    float nearestDist = FLT_MAX;	//FLT_MAX==float�^�̍ő�l

    for (auto&& node : _model.GetAllNodes())
    {
        //?�b�V?���܂܂�Ă��Ȃ��m�[�h�Ȃ��΂�
        if (node.Mesh == nullptr)continue;

        //���̃m�[�h��?�[?�h�s����擾
        Math::Matrix worldMat = node.LocalTransform * _mat;

        //�t�s��
        Math::Matrix inv = worldMat.Invert();

        //�t�s����g����?�[�J?���W�ɕϊ�
        Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
        Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

        //�g��s����g���Ă���?�b�V?�p��?�C�̒������v���Ă���
        float rayLen = localDir.Length();

        //�����͕K�������P�ɂ���
        localDir.Normalize();

        //?�b�V?���̑S�|?�S?����
        for (auto&& face : node.Mesh->GetFaces())
        {
            float dist;

            bool hit = DirectX::TriangleTests::Intersects(
                localPos,
                localDir,
                node.Mesh->GetVertexPositions()[face.Idx[0]],//�P���_�ڂ̍��W
                node.Mesh->GetVertexPositions()[face.Idx[1]],//�Q���_�ڂ̍��W
                node.Mesh->GetVertexPositions()[face.Idx[2]],//�R���_�ڂ̍��W
                dist	//?�C��?�������Ƃ���܂ł�?��(�Q�ƌ^)
            );

            if (hit == false)continue;

            //�g�啪�𔽉f
            dist /= rayLen;

            //�����Ƃ��߂�?�����c��
            if (dist < nearestDist)
            {
                nearestDist = dist;
            }
        }
    }
    if (nearestDist == FLT_MAX)
    {
        return false;
    }
    else {
        _dis = nearestDist;

        return true;
    }
}
bool ModelIntersects2(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, Math::Vector3& _normalVec, const Math::Vector3& _rayVec, float& _dis)
{
    float nearestDist = FLT_MAX;	//FLT_MAX==float�^�̍ő�l
    Math::Vector3 hitVPos[3];
    Math::Matrix hitMat;
    for (auto&& node : _model.GetAllNodes())
    {
        //?�b�V?���܂܂�Ă��Ȃ��m�[�h�Ȃ��΂�
        if (node.Mesh == nullptr)continue;

        //���̃m�[�h��?�[?�h�s����擾
        Math::Matrix worldMat = node.LocalTransform * _mat;

        //�t�s��
        Math::Matrix inv = worldMat.Invert();

        //�t�s����g����?�[�J?���W�ɕϊ�
        Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
        Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

        //�g��s����g���Ă���?�b�V?�p��?�C�̒������v���Ă���
        float rayLen = localDir.Length();

        //�����͕K�������P�ɂ���
        localDir.Normalize();

        //?�b�V?���̑S�|?�S?����
        for (auto&& face : node.Mesh->GetFaces())
        {
            float dist;
            Math::Vector3 vPos[3];
            vPos[0] = node.Mesh->GetVertexPositions()[face.Idx[0]];
            vPos[1] = node.Mesh->GetVertexPositions()[face.Idx[1]];
            vPos[2] = node.Mesh->GetVertexPositions()[face.Idx[2]];
            bool hit = DirectX::TriangleTests::Intersects(
                localPos,
                localDir,
                vPos[0],
                vPos[1],
                vPos[2],
                dist	//?�C��?�������Ƃ���܂ł�?��(�Q�ƌ^)
            );

            if (hit == false)continue;

            //�g�啪�𔽉f
            dist /= rayLen;

            //�����Ƃ��߂�?�����c��
            if (dist < nearestDist)
            {
                nearestDist = dist;

                hitVPos[0] = vPos[0];
                hitVPos[1] = vPos[1];
                hitVPos[2] = vPos[2];
                hitMat = worldMat;
            }
        }
    }
    if (nearestDist == FLT_MAX)
    {
        return false;
    }
    else 
    {
        _dis = nearestDist;
        Math::Vector3 vec1, vec2;
        vec1 = hitVPos[1] - hitVPos[0];
        vec2 = hitVPos[2] - hitVPos[0];
        _normalVec = DirectX::XMVector3Cross(vec1, vec2);
        _normalVec = DirectX::XMVector3TransformNormal(_normalVec, hitMat);
        _normalVec.Normalize();
        return true;
    }
}