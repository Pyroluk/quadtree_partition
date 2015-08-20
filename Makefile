WAF=./waf

nothing:


waf:
	wget http://www.freehackers.org/~tnagy/release/waf-1.8.7
	mv waf-1.8.7 waf
	python waf --version
	chmod +x waf

update:
	${WAF} build
	${WAF} install

all:
	${WAF} distclean
	${WAF} configure --prefix=${HOME}/local
	${WAF} build
	${WAF} install

verbose:
	${WAF} distclean
	${WAF} configure --prefix=${HOME}/local
	${WAF} -vvv build
	${WAF} install

test:
	TILETREE_ROOT="${HOME}/projects/tiletree" ./build/src/tiletree
