# my-library

自分用に整理する競技プログラミングライブラリ。[kyo-library](https://github.com/Kyo-s-s/Library) と
[maspypy/library](https://github.com/maspypy/library) から、実際に使う/使いそうな関数を移植したもの。

`ac-library` / `kyo-library` / `maspypy-library`（いずれも `~/` 直下に clone した外部ライブラリで
push権限が無い、または自分の管理下に無いリポジトリ）とは異なり、ここは `atcoder`（`Logi-1972`所有、push可能）
リポジトリの一部なので、いつでも自由に編集・整理・pushできる。

## 構成

```
my-library/
├── kyo/       # kyo-library からの移植(全17ファイル、自己完結)
│   ├── Data_structure/
│   ├── Math/
│   ├── String/
│   └── Template/
└── maspypy/   # maspypy-library からの移植(nt/・mod/全ファイル + ds/・graph/の抜粋 + 依存ファイル)
    ├── my_template.hpp
    ├── nt/
    ├── mod/
    ├── ds/
    ├── graph/
    ├── alg/       # 依存ファイル(モノイド定義等)
    ├── poly/      # 依存ファイル(畳み込み等)
    ├── enumerate/
    ├── linalg/
    ├── other/
    └── random/
```

- `kyo/`: 元の[docs/kyo-library.md](../docs/kyo-library.md)で紹介した全16ファイル(+Template.hpp)をそのまま移植。
  ヘッダ同士の相互includeが無く自己完結しているため、追加のファイルは不要。
- `maspypy/`: [docs/maspypy-library.md](../docs/maspypy-library.md)で紹介した135ファイル(nt/・mod/は全数論系、
  ds/・graph/はAtCoderでの使用頻度が高いものの抜粋)に加え、それらが内部で`#include`している依存ファイル
  (`alg/monoid/*.hpp`、`ds/bit_vector.hpp`、`poly/convolution.hpp`、`random/base.hpp`等、31ファイル)を
  自動解析して同梱し、**外部の`~/maspypy-library`が無くても単体でビルドできる**ようにしてある。

## 使い方

`mkprob`で作成した問題フォルダには `my-library` という名前でシンボリックリンクが自動生成される
(`~/atcoder/my-library` を指す)。

```cpp
#include <bits/stdc++.h>
using namespace std;
#include "my-library/maspypy/my_template.hpp"       // 基礎マクロ集(ll/vc/FOR/chmin等)。使うなら他より先に
#include "my-library/maspypy/nt/factor.hpp"          // 数論系の個別ヘッダ
#include "my-library/kyo/Data_structure/UnionFind.hpp" // kyo-library側の個別ヘッダ
```

- `my-library/kyo/...` は自己完結しているため `-I` フラグ不要。
- `my-library/maspypy/...` は内部でリポジトリルート相対のquoted include
  (`#include "nt/is_prime.hpp"`等)を使っているため、`build.sh`がソース中の
  `my-library/maspypy/`参照を検出すると自動で`-I./my-library/maspypy`を付与する。
- `my-library/kyo/` と `my-library/maspypy/` の両方に `UnionFind` があるなど、
  名前が重複するものが存在する。同時にincludeすると再定義エラーになるので、
  どちらか一方を選んで使うこと。

## 関数の使い方・シグネチャ

元の内容と同じなので、[docs/kyo-library.md](../docs/kyo-library.md) /
[docs/maspypy-library.md](../docs/maspypy-library.md) をそのまま参照できる
(ファイルパスは`kyo-library/`→`my-library/kyo/`、`maspypy-library/`→`my-library/maspypy/`と読み替える)。

## 今後の整理について

このディレクトリは今後、自分の好みに合わせて自由に手を加えていく想定
(不要な関数の削除、命名の統一、独自関数の追加など)。
`~/kyo-library` / `~/maspypy-library`（外部clone）を直接編集するのではなく、
必ずここ(`my-library/`)を編集すること。

## ライセンスについて

移植元の [Kyo-s-s/Library](https://github.com/Kyo-s-s/Library) と
[maspypy/library](https://github.com/maspypy/library) はいずれも明示的なライセンス表記が無いが、
競技プログラミングのコンテスト提出コードに自由にコピペして使うことを前提に公開されている
個人ライブラリであり、それに準じた個人利用の範囲で移植している。
