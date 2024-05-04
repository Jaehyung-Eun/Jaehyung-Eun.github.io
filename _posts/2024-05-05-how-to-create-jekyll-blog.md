---
layout: post
title:  "Jekyll 블로그 만들기"
date:   2024-05-05 01:28:00 +0900
categories: jekyll
---

# Jekyll 설치

jekyll을 사용하려면, ruby, gem, gcc, make 등이 필요합니다. 우선 apt 리포지토리를 최신 상태로 업데이트합니다. 그리고 루비와 함께 빌드에 필요한 패키지를 설치합니다.

```
sudo apt update && sudo apt upgrade -t
sudo apt install ruby-full build-essential zlib1g-dev -y
```

루비 젬의 경로를 bashrc에 추가합니다.

```
echo '# Install Ruby Gems to ~/gems' >> ~/.bashrc
echo 'export GEM_HOME="$HOME/gems"' >> ~/.bashrc
echo 'export PATH="$HOME/gems/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

jekyll을 설치합니다. 공식 문서에는 관리자 권한에 대한 이야기가 없지만, 스크립트를 실행하다보면 권한 오류가 납니다. 관리자 권한으로 gem을 설치합니다.

```
sudo gem install jekyll bundler
```

관리자 권한으로 myblog라는 이름의 새 jekyll 사이트를 생성합니다.

```
sudo jekyll new myblog
```

아래 명령을 통해 로컬 서버를 실행할 수 있습니다. 브라우저를 이용해 4000번 포트로 접속하면 블로그를 확인할 수 있습니다.

```
cd myblog
bundle exec jekyll serve
```

# 오류 처리

2024년 5월 기준 local server를 실행하면 다음과 같은 경고를 출력합니다.

```
Deprecation Warning: Using / for division outside of calc() is deprecated and will be removed in Dart Sass 2.0.0.

Recommendation: math.div($spacing-unit, 2) or calc($spacing-unit / 2)

More info and automated migrator: https://sass-lang.com/d/slash-div

   ╷
40 │   margin-bottom: $spacing-unit / 2;
   │                  ^^^^^^^^^^^^^^^^^
   ╵
    ../../../../minima-2.5.1/_sass/minima/_base.scss 40:18      @import
    minima.scss 48:3                                            @import
    /home/jaehyung/Jaehyung-Eun.github.io/assets/main.scss 1:9  root stylesheet
```

이 문제가 생기는 원인은 `jekyll-sass-converter-3.0.0`으로 인해 발생합니다. 아래 두 가지 방법 중 한 가지를 선택해서 해결할 수 있습니다.

* `jekyll-sass-converter-2.x`를 사용하도록 `Gemfile`을 수정한다.
* deprecation warning을 출력하지 않도록 `_config.yml` 파일을 수정한다.

이 문서에서는 `_config.yml` 파일을 수정해서 경고를 출력하지 않도록 수정하는 방법을 다룹니다. jekyll 개발진은 이 문제에 대해 인식하고 있으며, 수정을 완료했으나 아직 정식으로 release 되지 않은 상태라고 합니다. 

blog 디렉토리로 이동해서 `_config.yml` 파일에 `quiet_deps: true`를 추가합니다.

```
    echo '# disable deprecation warning' >> _config.yml
    echo 'sass:' >> _config.yml
    echo '  quiet_deps: true' >> _config.yml
```

출처: [https://github.com/jekyll/minima/issues/709](https://github.com/jekyll/minima/issues/709)