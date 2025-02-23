#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Para srand e rand

// Definições para direções do joystick
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define LED_MATRIX_ROWS 5
#define LED_MATRIX_COLS 5
#define GAME_TIME_LIMIT 10 // Segundos para completar o desafio

// Estrutura para armazenar a posição do ponto de luz
typedef struct {
    int x;
    int y;
} Point;

// Função para inicializar componentes
void initialize_hardware() {
    // Inicializa o joystick e a LED matrix como periféricos do BitDogLab
    // Aqui você deve implementar ou incluir as funções de inicialização reais
    // joystick_init();
    // led_matrix_init();
    // buzzer_init();
}

// Função para acender um ponto na matriz LED
void light_point(Point __attribute__((unused)) position) {
    // Aqui você deve implementar ou incluir a função real para acender o LED
    // led_matrix_set_pixel(position.x, position.y, 1); // 1 aqui representa LED aceso
}
// Função para apagar todos os LEDs
void clear_led_matrix() {
    for (int row = 0; row < LED_MATRIX_ROWS; row++) {
        for (int col = 0; col < LED_MATRIX_COLS; col++) {
            // Aqui você deve implementar ou incluir a função real para apagar o LED
            // led_matrix_set_pixel(row, col, 0); // 0 representa LED apagado
        }
    }
}

// Função principal do jogo
void play_game() {
    // Inicializa a semente para a função rand
    srand(time(NULL));

    Point target = {rand() % LED_MATRIX_ROWS, rand() % LED_MATRIX_COLS};
    Point current_position = {LED_MATRIX_ROWS / 2, LED_MATRIX_COLS / 2}; // Começa no centro
int time_left = GAME_TIME_LIMIT;
    
    while (time_left > 0) {
        clear_led_matrix();
        light_point(target);
        light_point(current_position);
        
        // Ler movimento do joystick
        // int joystick_direction = joystick_read();
        // Para testes, você pode usar uma entrada do usuário ou simular o movimento
        int joystick_direction = rand() % 4; // Simulação de movimento aleatório
        
        // Atualiza a posição baseada na leitura do joystick
        switch(joystick_direction) {
            case UP: if (current_position.y > 0) current_position.y--; break;
            case DOWN: if (current_position.y < LED_MATRIX_COLS - 1) current_position.y++; break;
            case LEFT: if (current_position.x > 0) current_position.x--; break;
            case RIGHT: if (current_position.x < LED_MATRIX_ROWS - 1) current_position.x++; break;
        }
        
        // Verifica se o jogador alcançou o alvo
        if (current_position.x == target.x && current_position.y == target.y) {
            // buzzer_play(440, 500); // Toca um tom de 440 Hz por 500 ms
            printf("Jogador venceu!\n");
            return; // Jogador venceu
        }

        // Decrementa o tempo
        time_left--;
        // Simulação de delay (não é a melhor prática para produção)
        for (volatile int i = 0; i < 1000000; i++);
    }
    // buzzer_play(220, 1000); // Toca um tom baixo para indicar derrota
    printf("Jogador perdeu!\n");
}

int main() {
    initialize_hardware();
    while(1) {
        play_game();
        // Aqui você pode adicionar uma lógica para reiniciar o jogo ou encerrar
    }
    return 0;
}