import subprocess

def test_map_correct():
    with open("test_ok.cub", "w") as f:
        f.write("NO assets/texture/bendy.xpm\nSO assets/texture/bendy.xpm\nEA assets/texture/bendy.xpm\nWE assets/texture/bendy.xpm\nC 46,7,7\nF 36,6,6\n111111\n10N001\n111111\n")
    result = subprocess.run(
        ["./cub3d", "test_ok.cub"],
        capture_output=True,
        text=True
    )
    subprocess.run(["rm", "-rf", "test_ok.cub"])
    assert "Error" not in result.stdout

def test_map_not_found():
    result = subprocess.run(
        ["./cub3d", "unknown.cub"],
        capture_output=True,
        text=True
    )
    assert "Error" in result.stdout

def test_map_is_dir():
    result = subprocess.run(
        ["./cub3d", "/bin/"],
        capture_output=True,
        text=True
    )
    assert "Error" in result.stdout

def test_map_permiss():
    subprocess.run(["touch", "forbidden.cub"])
    subprocess.run(["chmod", "000", "forbidden.cub"])
    result = subprocess.run(
        ["./cub3d", "forbidden.cub"],
        capture_output=True,
        text=True
    )
    subprocess.run(["rm", "-rf", "forbidden.cub"])
    assert "Error" in result.stdout

def test_map_invalid():
    with open("invalid.cub", "w") as f:
        f.write("NO assets/texture/bendy.xpm\nC 999,999,999\nF 36,6,6\n111111\n100001\n111111\n")
    result = subprocess.run(
        ["./cub3d", "invalid.cub"],
        capture_output=True,
        text=True
    )
    subprocess.run(["rm", "-rf", "invalid.cub"])
    assert "Error" in result.stdout

#============VALGRIND_TESTER================

def test_valgrind_ok():
    with open("test_ok.cub", "w") as f:
        f.write("NO assets/texture/bendy.xpm\nSO assets/texture/bendy.xpm\nEA assets/texture/bendy.xpm\nWE assets/texture/bendy.xpm\nC 46,7,7\nF 36,6,6\n111111\n10N001\n111111\n")
    result = subprocess.run(
        [
            "valgrind",
            "--leak-check=full",
            "--show-leak-kinds=all",
            "--track-origins=yes",
            "./cub3d",
            "test_ok.cub"
        ],
        capture_output=True,
        text=True
    )
    subprocess.run(["rm", "-rf", "test_ok.cub"])
    # Checa se não há leaks
    output = result.stdout + result.stderr
    assert (
        "in use at exit: 0 bytes in 0 blocks" in output
       or (
           "in use at exit: 27 bytes in 2 blocks" in output
          and "definitely lost: 0 bytes" in output
       )
    )

def test_valgrind_invalid():
    with open("invalid.cub", "w") as f:
        f.write("NO assets/texture/bendy.xpm\nC 999,999,999\nF 36,6,6\n111111\n100001\n111111\n")
    result = subprocess.run(
        [
            "valgrind",
            "--leak-check=full",
            "--show-leak-kinds=all",
            "--track-origins=yes",
            "./cub3d",
            "invalid.cub"
        ],
        capture_output=True,
        text=True
    )
    subprocess.run(["rm", "-rf", "invalid.cub"])
    # Checa se não há leaks
    output = result.stdout + result.stderr
    print (output)
    assert (
        "in use at exit: 0 bytes in 0 blocks" in output
       or (
           "in use at exit: 27 bytes in 2 blocks" in output
          and "definitely lost: 0 bytes" in output
       )
    )

def test_valgrind_invalid():
    result = subprocess.run(
        [
            "valgrind",
            "--leak-check=full",
            "--show-leak-kinds=all",
            "--track-origins=yes",
            "./cub3d",
            "maps/invalids/dup_textures.cub"
        ],
        capture_output=True,
        text=True
    )
    output = result.stdout + result.stderr
    print (output)
    assert (
        "in use at exit: 0 bytes in 0 blocks" in output
       or (
           "in use at exit: 27 bytes in 2 blocks" in output
          and "definitely lost: 0 bytes" in output
       )
    )
