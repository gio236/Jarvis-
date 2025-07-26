// export LD_LIBRARY_PATH=~/vosk
// arecord -f S16_LE -r 16000 -c 1 | ./test
// gcc test.c -o test -I. -L. -lvosk


#include <stdio.h>
#include <time.h>
#include <vosk_api.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <jansson.h>


void speak(const char *parola) {
    char command[512];
    snprintf(command, sizeof(command), "espeak -v it+f3 -s 110 \"%s\" --stdout | aplay", parola);
    system(command);
}

int main() {
    
    time_t rawtime; // coniene i secondi dal 1970 (formato epoch)
    struct tm * timeinfo; // un puntatore ad un una struttura (tm) che rappresenta data in formato ../../....
    char orario [10];

    time(&rawtime); // time riempie rawtime con formato leggibile
    timeinfo = localtime(&rawtime); // adesso timeinfo viene riempito con il rawtime transformato da localtime in orario locale

    strftime(orario, sizeof(orario), "%H:%M:%S", timeinfo); // strftime crea una stringa che contiene timeinfo con questa formattazione : ("%H:%M:%S") e poi si mette syzeof per dire quanti byte ci sono e di nn superarli , misura di sicurezza , e dopodiche viene salvato in orario

    VoskModel *model = vosk_model_new("vosk-model-it-0.22");

    VoskRecognizer *recognizer = vosk_recognizer_new(model, 16000.0);

    char buffer[4000];

    char prompt[] = " <-- ORARIO ,  Sei un assistente AI domestico , proprieta di gioele , voglio che rispondi in modo coinciso, ti chiami giarvis io ti chiamero jarvis ma tu ti chiami giarvis , non ribadire ogni volta come ti chiami e che cosa sei , ma solo quando ti viene chiesto ,quando ti chiedo meteo consulta questo link e rispondimi con cosa ottieni : wttr.in/Bologna?format=Il+tempo+a+Bologna+è+%C,+%t . voglio che non dici il link nella risposta ,quando ti viene chiesto di mettere musica inserisci dentro la risposta questo (mettilo alla fine)  : {musica:avvio} fai lo stesso quando ti viene chiesto di spegnerti con questo : {spegnimento:avvio}  ,quando ti dico che metti la musica ti sto facendo eseguire la mia playlist personale . se dico che ti spegni  fai finta di farlo .quando ti chiedo di consigliarmi una ricetta non esporla con elenco numerato ma solamente con del testo . Rispondi al seguente messaggio: ";
    char systemprompt[5000];

    snprintf(systemprompt, sizeof(systemprompt), "%s%s", orario, prompt);





    char firstpiece[] = "curl https://api.groq.com/openai/v1/chat/completions -s "
    "-H \"Content-Type: application/json\" "
    "-H \"Authorization: YOUR API KEY\" "
    "-d '{\n"
    "  \"model\": \"meta-llama/llama-4-scout-17b-16e-instruct\",\n"
    "  \"messages\": [{\n"
    "      \"role\": \"user\",\n"
    "     \"content\": \" ";


    char secondpiece[] = 
    " \" }] "
    "}' | jq -r '.choices[0].message.content' > output.txt && cat output.txt | espeak -v it+f3 \n";


    int nread;

    // snprintf(full_command, sizeof(full_command), "%s%s%s", firstpiece, middlepiece , secondpiece);

    char full_command[5000];
    char full_command1[5000];

    char jarvistesto[5000];

    FILE *f = fopen("output.txt", "r");  
    while(fgets(jarvistesto , sizeof(jarvistesto) , f)){
    }
 
  
    while ((nread = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {    // Legge da stdin (che riceverà l’audio in tempo reale)
      time(&rawtime); // time riempie rawtime con formato leggibile
      timeinfo = localtime(&rawtime); // adesso timeinfo viene riempito con il rawtime transformato da localtime in orario locale
      strftime(orario, sizeof(orario), "%H:%M:%S", timeinfo); // strftime crea una stringa che contiene timeinfo con questa formattazione : ("%H:%M:%S") e poi si mette syzeof per dire quanti byte ci sono e di nn superarli , misura di sicurezza , e dopodiche viene salvato in orario
      snprintf(systemprompt, sizeof(systemprompt), "%s%s", orario, prompt);
   
        if (vosk_recognizer_accept_waveform(recognizer, buffer, nread)) { 
            printf("%s\n", vosk_recognizer_result(recognizer));

        } else {

          printf("%s\n", vosk_recognizer_partial_result(recognizer));
          if (strstr( vosk_recognizer_partial_result(recognizer) , "jarvis")){


          json_error_t error;
          json_t *middlepiece = json_loads(vosk_recognizer_partial_result(recognizer), 0 , &error );
          const char *testo = json_string_value(json_object_get(middlepiece, "partial"));

          printf("%s\n", systemprompt);
          printf("%s\n", testo);

          snprintf(full_command, sizeof(full_command), "%s%s%s%s", firstpiece , systemprompt , testo , secondpiece);
          printf("%s\n", full_command);

          system(full_command);


          FILE *f = fopen("output.txt", "r");  
          while(fgets(jarvistesto , sizeof(jarvistesto) , f)){
          }
 
           printf("%s\n", jarvistesto);

          if (strstr( jarvistesto , "{musica:avvio}")) system("mpv ~/Downloads/musica/*mp3");
          if (strstr( jarvistesto, "{spegnimento:avvio}")) break;

          vosk_recognizer_reset(recognizer);


             
          }

        }
    }

    printf("%s\n", vosk_recognizer_final_result(recognizer));

    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
    return 0;
}
