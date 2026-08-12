FetchContent_Declare(
	spdlog
	GIT_REPOSITORY	https://github.com/gabime/spdlog.git
	GIT_TAG			v1.14.0
	GIT_SHALLOW     TRUE
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(spdlog)
