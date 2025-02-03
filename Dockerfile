# --- Base Stage ---
	FROM debian:bookworm-slim AS base

	WORKDIR /app

	# Install essential build tools and core dependencies
	RUN apt-get update && \
			apt-get install -y build-essential cmake libcmocka-dev clang clang-tidy clang-format cppcheck

	# Copy the project files
	COPY . /app

	# --- Development Stage ---
	FROM base AS development

	# # Install debugging tools (optional)
	# RUN apt-get update && \
	# 		apt-get install -y gdb valgrind

	# Set default build type to Debug
	ENV CMAKE_BUILD_TYPE=Debug

	# --- Testing Stage ---
	FROM base AS testing

	# Set build type to Debug for optimized test runs
	ENV CMAKE_BUILD_TYPE=Debug

	# Use build.sh for building
	COPY scripts/build.sh /app/scripts/
	RUN /app/scripts/build.sh /app/build

  # --- Staging Stage ---
	FROM base AS staging

	# Set build type to Release
	ENV CMAKE_BUILD_TYPE=Release

	# Build the project for staging
	RUN cmake -B /app/build -S /app -DCMAKE_BUILD_TYPE=Release && \
			cmake --build /app/build --config Release

	# Expose a volume for storing results (optional)
	VOLUME /app/results

	# Set the working directory
	WORKDIR /app

	# Copy the test script
	COPY scripts/test_encryption.sh /app/scripts/

	# Run the encryption/decryption test script
	CMD ["/app/scripts/test_encryption.sh"]

	# --- Production Stage ---
	FROM base AS production

	# Set build type to Release
	ENV CMAKE_BUILD_TYPE=Release

	# Use build.sh for building
	COPY scripts/build.sh /app/scripts/
	RUN /app/scripts/build.sh /app/build

	# --- Final Production Image (Optional) ---
	# This creates a very small image with only the production executable
	FROM debian:bookworm-slim AS final-production

	# Copy only the compiled executable from the production stage
	COPY --from=production /app/build/evo /usr/bin/evo

	# Set the entry point for the container
	ENTRYPOINT ["/usr/bin/evo"]
