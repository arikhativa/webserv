

# git clone --depth=50 --branch=main https://github.com/arikhativa/webserv.git arikhativa/webserv
# cd arikhativa/webserv
# COMMIT=$(git rev-parse HEAD); git checkout -qf $COMMIT


ci/local:
	docker run -it travisci/ci-garnet:packer-1515445631-7dfb2e1 /bin/bash