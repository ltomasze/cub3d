Plan wykonania kodu krok po kroku
Sprawdzenie argumentów wejściowych

Funkcja check_args(argc, argv) weryfikuje poprawność podanych argumentów.
Jeśli argumenty są nieprawidłowe, program zwraca 1 i kończy działanie.
Inicjalizacja MLX i utworzenie okna

mlx = mlx_init(); – inicjalizuje bibliotekę MiniLibX.
win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D"); – tworzy okno o określonych wymiarach.
Jeśli inicjalizacja MLX lub utworzenie okna się nie powiodło, program wyświetla komunikat błędu i kończy działanie.
Przypisanie wskaźników MLX do struktury cub3d

ft_assign_mlx(&cub3d, mlx, win); – zapisuje wskaźniki do struktury cub3d, aby były dostępne w całym programie.
Ukrycie kursora myszy w oknie gry

mlx_mouse_hide(cub3d.mlx, cub3d.win); – ukrywa kursor myszy w oknie gry (przydatne dla gier FPS).
Inicjalizacja struktury cub3d

ft_init_cub3d(&cub3d, argv); – wczytuje dane gry na podstawie argumentów wejściowych.
Jeśli inicjalizacja się nie powiedzie, program kończy działanie.
Sprawdzenie, czy mapa jest zamknięta

ft_check_map_closed(cub3d.map); – sprawdza, czy mapa gry jest poprawnie zamknięta.
Jeśli mapa ma otwarte krawędzie, program kończy działanie.
Ustawienie domyślnego stanu gry

ft_set_default_state(&cub3d); – ustawia początkowe wartości zmiennych gry.
Podłączenie głównej pętli renderowania

mlx_loop_hook(mlx, main_loop, &cub3d); – ustawia główną funkcję renderującą (main_loop) jako pętlę obsługi logiki gry.
Obsługa zdarzeń (klawiatura, mysz itp.)

ft_handle_hooks(&cub3d); – rejestruje funkcje obsługi wejścia użytkownika.
Uruchomienie głównej pętli MLX

mlx_loop(mlx); – rozpoczyna główną pętlę renderowania i obsługi zdarzeń, która działa do momentu zamknięcia okna gry.
