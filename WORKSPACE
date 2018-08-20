http_archive(
    name = "io_bazel_rules_python",
    sha256 = "8b32d2dbb0b0dca02e0410da81499eef8ff051dad167d6931a92579e3b2a1d48",
    strip_prefix = "rules_python-8b5d0683a7d878b28fffe464779c8a53659fc645",
    urls = ["https://github.com/bazelbuild/rules_python/archive/8b5d0683a7d878b28fffe464779c8a53659fc645.tar.gz"],
)

load("@io_bazel_rules_python//python:pip.bzl", "pip_repositories", "pip_import")

pip_repositories()

pip_import(
    name = "pip_requirements",
    requirements = "//:requirements.txt",
)

load("@pip_requirements//:requirements.bzl", "pip_install")

pip_install()

new_local_repository(
    name = "local_boost",
    build_file = "third_party/boost.BUILD",
    path = "/usr/",
)

bind(
    name = "boost",
    actual = "@local_boost//:boost",
)
