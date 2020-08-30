
# include <Siv3D.hpp> 
void Main()
{
    //背景色
    Scene::SetBackground(Palette::White);


    //ボールの座標,大きさ(x座標,y座標,半径8)
    Circle ball(400, 400, 8);

    //ボール速さ
    constexpr double speed = 480.0;

    //ボール速度
    Vec2 ballVelocity(0, -speed);

    //ブロックサイズ
    constexpr Size blockSize(40, 20);

    // ブロックの座標,サイズ
    Array<Rect> blocks =
    {
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize),
        Rect(Random(760), Random(300) ,blockSize), Rect(Random(760), Random(300) ,blockSize)
    };

    while (System::Update())
    {

        // パドルの座標,大きさ((x座標マウス,y座標)横,縦)
        const Rect paddle(Arg::center(Cursor::Pos().x, 500), 60, 10);

        // ボールを移動
        ball.moveBy(ballVelocity * Scene::DeltaTime());

        // ブロックを順にチェック
        for (auto it = blocks.begin(); it != blocks.end(); ++it)
        {
            // ボールとブロックが交差していたら
            if (it->intersects(ball))
            {
                // ボールの向きを反転する
                (it->bottom().intersects(ball) || it->top().intersects(ball) ? ballVelocity.y : ballVelocity.x) *= -1;

                // ブロックを配列から削除（イテレータが無効になるので注意）
                blocks.erase(it);

                // これ以上チェックしない  
                break;
            }
        }


        // 天井にぶつかったらはね返る
        if (ball.y < 0 && ballVelocity.y < 0)
        {
            ballVelocity.y *= -1;
        }

        // 左右の壁にぶつかったらはね返る
        if ((ball.x < 0 && ballVelocity.x < 0) || (Scene::Width() < ball.x && ballVelocity.x > 0))
        {
            ballVelocity.x *= -1;
        }

        // パドルにあたったらはね返る
        if (ballVelocity.y > 0 && paddle.intersects(ball))
        {
            // パドルの中心からの距離に応じてはね返る向きを変える
            ballVelocity = Vec2((ball.x - paddle.center().x) * 10, -ballVelocity.y).setLength(speed);
        }



        // ボールを描く
        ball.draw(ColorF(0, 0, 0));

        //ブロックを描く
        for (const auto& block : blocks)
        {
            block.draw(ColorF(0, 0, 0));
        }
        //パドルを描く
        paddle.draw(ColorF(0, 0, 0));
    }
}