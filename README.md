# Usage
```
docker-compose exec builder bash

## プラグインビルドとインストール
# make

## プラグイン実行テスト
## 下記のような感じ、動画ファイルは適当に持ってきて
gst-launch-1.0 -v filesrc location=test.mp4 ! decodebin ! video/x-raw,format=I420 ! identity ! saveframesink
```
