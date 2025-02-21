# Configuración.
BASE_NAME = heliostat_tracking

# Sesión en el devcontainer principal Python.
python_sesion:
	@docker exec -ti \
		--workdir $(shell pwd) \
		$(BASE_NAME)_python \
		/bin/bash

# Limpia activos.
clean:
	@read -p "¿Eliminar infraestructura Docker [s/N]? " confirm && \
	if [ "$$confirm" = "s" ]; then \
		docker ps --filter name=$(BASE_NAME)* -q | xargs docker stop -t0; \
		docker ps -a --filter name=$(BASE_NAME)* -q | xargs docker rm; \
		docker image ls --filter reference=*$(BASE_NAME)* -q | xargs docker image rm; \
		docker network ls --filter name=$(BASE_NAME) -q | xargs docker network rm; \
	fi

# Ejecuta cmake para hacer el build dentro del DevContainer.
build:
	@cmake -S . -B build
	@cd ./build && make

# Limpia el build dentro del DevContainer.
build_clean:
	@rm -Rf build

# Instala en el DevContainer los productos.
install:
	@chmod 755 build/bluesolar_*
	@cp build/bluesolar_* /usr/local/bin
	@cp build/libheliostat_tracking.so /usr/local/lib

# Testea la instalación.
test:
	@echo Debe devolver 37.5801, -2.37526, 0.355814, 0.293007
	@bluesolar_angles \
		0 100 0 \
		0 0 20 \
		170 65

	@echo Debe devolver -0.000171089, 0, 20
	@bluesolar_points \
		0 100 0 \
		170 65 \
		0 \
		0.355814 0.293007

# Crea un directorio dist con lo que se necesita para otros
# containers:
dist:
	@rm -Rf dist
	@mkdir -p dist/bin
	@mkdir -p dist/lib

	@chmod 755 build/bluesolar_*
	@cp build/bluesolar_* dist/bin
	@cp build/libheliostat_tracking.so dist/lib

	@echo "#!/bin/bash" > dist/install.sh
	@echo "cp bin/bluesolar_angles /usr/local/bin" >> dist/install.sh
	@echo "cp bin/bluesolar_points /usr/local/bin" >> dist/install.sh
	@echo "cp lib/libheliostat_tracking.so /usr/local/lib" >> dist/install.sh

	@chmod 755 dist/install.sh

.PHONY: build test dist