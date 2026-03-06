pipeline {
	agent {
		label "built-in"
	}
	stages {
		stage("Build") {
			parallel {
				stage("Build for Linux 64-bit") {
					agent {
						label "built-in"
					}
					steps {
						sh("git submodule update --init --recursive --force")
						sh("make -j4 CC=musl-gcc LDFLAGS=-static")
						sh("mv taiga taiga-linux64")
						archiveArtifacts("taiga-linux64")
					}
				}
				stage("Build for Linux 64-bit (Debug)") {
					agent {
						label "built-in"
					}
					steps {
						sh("git submodule update --init --recursive --force")
						sh("make -j4 CC='musl-gcc -g' LDFLAGS=-static")
						sh("mv taiga taiga-debug-linux64")
						archiveArtifacts("taiga-debug-linux64")
					}
				}
				stage("Build for Windows 32-bit") {
					agent {
						label "built-in"
					}
					environment {
						WATCOM = "/usr/watcom"
						INCLUDE = "/usr/watcom/h:/usr/watcom/h/nt"
						PATH = "/usr/watcom/binl64:${env.PATH}"
					}
					steps {
						sh("git submodule update --init --recursive --force")
						sh("make -j4 -f Makefile.watcom")
						sh("mv taiga.exe taiga-win32.exe")
						archiveArtifacts("taiga-win32.exe")
					}
				}
			}
			post {
				always {
					notifyDiscord()
				}
			}
		}
	}
}
