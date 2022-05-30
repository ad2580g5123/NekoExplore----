#include "headers.h"
bool ModelIntersects(const KdModel& _model, const Math::Matrix& _mat, const Math::Vector3& _rayPos, const Math::Vector3& _rayVec, float& _dis)
{

    float nearestDist = FLT_MAX;	//FLT_MAX==float型の最大値

    for (auto&& node : _model.GetAllNodes())
    {
        //?ッシ?が含まれていないノードなら飛ばす
        if (node.Mesh == nullptr)continue;

        //そのノードの?ー?ド行列を取得
        Math::Matrix worldMat = node.LocalTransform * _mat;

        //逆行列化
        Math::Matrix inv = worldMat.Invert();

        //逆行列を使って?ーカ?座標に変換
        Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
        Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

        //拡大行列を使っている?ッシ?用に?イの長さを計っておく
        float rayLen = localDir.Length();

        //方向は必ず長さ１にする
        localDir.Normalize();

        //?ッシ?内の全ポ?ゴ?を回す
        for (auto&& face : node.Mesh->GetFaces())
        {
            float dist;

            bool hit = DirectX::TriangleTests::Intersects(
                localPos,
                localDir,
                node.Mesh->GetVertexPositions()[face.Idx[0]],//１頂点目の座標
                node.Mesh->GetVertexPositions()[face.Idx[1]],//２頂点目の座標
                node.Mesh->GetVertexPositions()[face.Idx[2]],//３頂点目の座標
                dist	//?イが?たったところまでの?離(参照型)
            );

            if (hit == false)continue;

            //拡大分を反映
            dist /= rayLen;

            //もっとも近い?離を残す
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
    float nearestDist = FLT_MAX;	//FLT_MAX==float型の最大値
    Math::Vector3 hitVPos[3];
    Math::Matrix hitMat;
    for (auto&& node : _model.GetAllNodes())
    {
        //?ッシ?が含まれていないノードなら飛ばす
        if (node.Mesh == nullptr)continue;

        //そのノードの?ー?ド行列を取得
        Math::Matrix worldMat = node.LocalTransform * _mat;

        //逆行列化
        Math::Matrix inv = worldMat.Invert();

        //逆行列を使って?ーカ?座標に変換
        Math::Vector3 localPos = DirectX::XMVector3Transform(_rayPos, inv);
        Math::Vector3 localDir = DirectX::XMVector3TransformNormal(_rayVec, inv);

        //拡大行列を使っている?ッシ?用に?イの長さを計っておく
        float rayLen = localDir.Length();

        //方向は必ず長さ１にする
        localDir.Normalize();

        //?ッシ?内の全ポ?ゴ?を回す
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
                dist	//?イが?たったところまでの?離(参照型)
            );

            if (hit == false)continue;

            //拡大分を反映
            dist /= rayLen;

            //もっとも近い?離を残す
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