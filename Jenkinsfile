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
						archiveArtifacts("taiga")
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
