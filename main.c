//Se vuoi salvare un informazione nella memoria a lungo termine devi rispondere in formato JSON valido con tre campi esatti risposta azione e aggiornamento Il campo azione deve essere aggiornamento memoria Il campo aggiornamento deve contenere esattamente il testo che vuoi salvare in memoria per il futuro Ogni volta che la memoria viene aggiornata quel contenuto verrà caricato come prompt di sistema ogni volta che verrai riavviato o richiamato Non scrivere nulla fuori dal blocco JSON Nessun commento nessun testo extra nessun carattere fuori dal JSON Se non vuoi aggiornare la memoria il campo aggiornamento deve essere una stringa vuota
//
//
//
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


void strip_newline(char *str) {
    size_t len = strlen(str);
    if (len == 0) return;

    if (str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void speak(const char *parola) {
    char command[512];
    snprintf(command, sizeof(command), "/home/gioele/.local/bin/gtts-cli \"%s\" --lang it --output voce.mp3 && mpv voce.mp3", parola);
    system(command);
}

// ~/.local/bin/gtts-cli "

int main() {
    
    time_t rawtime; // coniene i secondi dal 1970 (formato epoch)
    struct tm * timeinfo; // un puntatore ad un una struttura (tm) che rappresenta data in formato ../../....
    char orario [10];
    char orario1 [20];

    time(&rawtime); // time riempie rawtime con formato leggibile
    timeinfo = localtime(&rawtime); // adesso timeinfo viene riempito con il rawtime transformato da localtime in orario locale

    strftime(orario, sizeof(orario), "%H:%M:%S", timeinfo); // strftime crea una stringa che contiene timeinfo con questa formattazione : ("%H:%M:%S") e poi si mette syzeof per dire quanti byte ci sono e di nn superarli , misura di sicurezza , e dopodiche viene salvato in orario
    VoskModel *model = vosk_model_new("vosk-model-it-0.22");
    VoskRecognizer *recognizer = vosk_recognizer_new(model, 16000.0);
    snprintf(orario1, sizeof(orario1), "%s <-- ORARIO", orario);

    char buffer[4000];
    char telegrammessage[4000];
         



//******************************************************************************meteo****************************************************************************

  system("curl wttr.in/Bologna?format=Il+tempo+a+Bologna+è+%C,+%t -o meteo.txt -s");

  char meteo[60];
  char meteo1[75];

  FILE *tempo = fopen("meteo.txt", "r");  
  while(fgets(meteo , sizeof(meteo) , tempo)){
  }
  fclose(tempo);

  snprintf(meteo1, sizeof(meteo1), "%s <-- METEO ", meteo);

      
//******************************************************************************meteo****************************************************************************

    char full_command[5000];
    char full_command1[5000];

    system("echo '[]' > history.json");
    system("date > date.txt");
    char data[60];

    FILE *date = fopen("date.txt", "r");  
    while(fgets(data , sizeof(data) , date)){
    }
    fclose(date);
 
//******************************************************************************meteo****************************************************************************

    char memoria[5000];
    char memoriajson[5200];
    FILE *memory = fopen("memoria.txt", "r");  
    while(fgets(memoria, sizeof(memoria) , memory)){
    }
    fclose(memory);
 
 
   // char prompt[] = "questo comando lo dovrai inserire quando ti chiedero il meteo alla fine della risposta : {meteo:avvio} , Sei un assistente AI domestico , proprieta di gioele , voglio che rispondi in modo coinciso, non devi inserire caratteri speciali ammenoche non ti venga chiesto o viroglette nel testo ,ti chiami giarvis io ti chiamero jarvis o darwin NON DIRE MAI CHE NON TI CHIAMI DARWIN, non ribadire ogni volta come ti chiami e che cosa sei , ma solo quando ti viene chiesto ,dimmi il meteo solo se chiesto . voglio che non dici il link nella risposta ,devi inserire questo solo quando ti viene chiesto di mettere musica inserisci alla fine della risposta questo : {musica:avvio} in caso ti venisse chiesto di mettere musica su laptop1 inserisci {musica1:avvio} . fai lo stesso quando ti viene chiesto di spegnerti con questo : {spegnimento:avvio}  ,invece se ti chiedo di spegnere lapotp1 , inserisci questo : {spegnimento1:avvio} ,quando ti dico che metti la musica ti sto facendo eseguire la mia playlist personale . se dico che ti spegni  fai finta di farlo . nella tua risposte non usare elenchi ordinati o non ordinati ma solo e semplice teso , questo detto fino ad ora era solo un prompt di sistema la domanda a cui devi rispondere e questa : ";
    char prompt[] = "ti chiami jarvis ma io ti posso chiamare anche darwin,Devi rispondere esclusivamente in formato JSON valido, con esattamente due campi: risposta e azione. Il campo risposta deve contenere la tua risposta testuale per utente. Il campo azione deve contenere, se necessario, uno dei seguenti identificatori precisi che attiveranno comandi specifici: musica per far partire la musica in locale, musica1 per far partire la musica su laptop1 tramite ssh, spegnimento per spegnere assistente, spegnimento1 per spegnere laptop1 tramite ssh, meteo per mostrare le previsioni del tempo. Se non è necessaria nessuna azione, il campo azione deve restare una stringa vuota. Non devi mai scrivere nulla fuori dal blocco JSON. Non inserire spiegazioni, commenti o caratteri non validi. Se non rispetti esattamente questo formato, la tua risposta sarà ignorata e non utile.";
    char systemprompt[5000];
    char promptjson[5000];
    char datejson[5000];
    char jarvisnoncapisceuncazzo[5000] = "IMPORTANTE Rispondi esclusivamente in formato JSON valido Ogni risposta deve essere un oggetto JSON con due campi esatti risposta e azione Non devi scrivere nulla prima o dopo il blocco JSON Nessun commento nessun testo extra nessun carattere fuori dal JSON Se l utente ti scrive grazie la risposta corretta sarà risposta Prego Se hai bisogno di altro sono qui azione Se violi questa regola il sistema ignorerà la tua risposta Comandi validi nel campo azione meteo musica musica1 spegnimento spegnimento1";
    char jarvisnoncapisceuncazzo1[] = "Rispondi esclusivamente in JSON valido. Non includere testo fuori dal formato JSON";
    char json12[5000];
    char datejson1[500];
    char abitudini[2000] = "Queste informazioni servono solo come contesto personale. Non devi menzionarle, ripeterle o farne riferimento diretto, a meno che il contesto non lo renda assolutamente rilevante. Usa il tuo buon senso per capire quando applicarle in modo implicito. Ti conosco già: sei il mio assistente AI personale. Ecco cosa devi sapere di me: - Mi chiamo Gioele, ho 15 anni e vivo a Bologna. - Frequento un ITIS (indirizzo informatica) e sto per iniziare il terzo anno. - Sono appassionato di informatica e del mondo Marvel. - Il mio supereroe preferito è Spider-Man, seguito da Iron Man. - Amo guardare film: ho un abbonamento a Netflix, ma uso anche siti di streaming alternativi. - Adoro la pizza. - Ora è estate, (sono anche un po asociale) e preferisco restare a casa: sviluppo il mio assistente (cioè te) e gioco spesso a Roblox. - Uso un laptop Lenovo ThinkPad T530, che per te si chiama 'laptop1'. - Non ho veri amici nella vita reale, quindi passo molto tempo da solo o online. Non usare o citare esplicitamente queste informazioni. Usale solo per comprendere meglio i miei interessi, il mio stile di vita e il mio modo di comunicare.";
    char abitudinijson[2000];
    char aggiornomemo[2000] = "Se vuoi salvare un informazione nella memoria a lungo termine devi rispondere in formato JSON valido con tre campi esatti risposta azione e aggiornamento Il campo azione deve essere : ,aggiornamento memoria, Il campo aggiornamento deve contenere esattamente il testo che vuoi salvare in memoria per il futuro Ogni volta che la memoria viene aggiornata quel contenuto verrà caricato come prompt di sistema ogni volta che verrai riavviato o richiamato Non scrivere nulla fuori dal blocco JSON Nessun commento nessun testo extra nessun carattere fuori dal JSON Se non vuoi aggiornare la memoria il campo aggiornamento deve essere una stringa vuota";
    char aggiornomemojson[2000];
    char notify[2000] = "se ti chiedo di impostare promemoria o di ricordarmi qualcosa metti nel campo azione : invio notifica , ed crei 2 campi uno che si chiama : tempo , in cui inseriai il tempo che bisgona aspettare prima di inviare la notifica esempio : se ti chiedo di impostare un promemoria tra 30 minuti il tempo sara 1800 , devi sempre mettere in secondi , ed inoltre devi creare campo che si chiama : notifica , che contiene il testo da ricordare quindi se ti chiedo di farmi ricordare di andare a fare la spesa tra 30 minuti i campi saranno cosi : tempo : 18000 , notifica : fare la spesa ";
    char notifyjson[2000];
    char azionetesto[2000];

    snprintf(systemprompt, sizeof(systemprompt), "%s , %s , %s", orario1,meteo1, prompt);

    snprintf(promptjson, sizeof(promptjson), "{\"role\": \"system\", \"content\": \"%s\"}"  , systemprompt);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",promptjson);
    system(full_command1);

    snprintf(notifyjson, sizeof(notifyjson), "{\"role\": \"system\", \"content\": \"%s\"}"  , notify);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",notifyjson);
    system(full_command1);

    snprintf(memoriajson, sizeof(memoriajson), "{\"role\": \"system\", \"content\": \"%s\"}"  , memoria);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",memoriajson);
    system(full_command1);

    snprintf(aggiornomemojson, sizeof(aggiornomemojson), "{\"role\": \"system\", \"content\": \"%s\"}"  , aggiornomemo);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",aggiornomemojson);
    system(full_command1);

    snprintf(json12, sizeof(json12), "{\"role\": \"system\", \"content\": \"%s\"}"  , jarvisnoncapisceuncazzo);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",json12);
    system(full_command1);

    snprintf(datejson, sizeof(datejson), "{\"role\": \"system\", \"content\": \"DATA ODIERNA : %s\"}"  , data);
    snprintf(datejson1, sizeof(datejson1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",datejson);
    system(datejson1);
 
    snprintf(abitudinijson, sizeof(abitudinijson), "{\"role\": \"system\", \"content\": \"%s\"}"  , abitudini);
    snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ",abitudinijson);
    system(full_command1);
 

/*
curl -s https://api.groq.com/openai/v1/chat/completions \
  -H "Authorization: Bearer " \
  -H "Content-Type: application/json" \
  -d "{
    \"model\": \"meta-llama/llama-4-scout-17b-16e-instruct\",
    \"messages\": $(cat history.json)
  }"

*/

    int nread;

    // snprintf(full_command, sizeof(full_command), "%s%s%s", firstpiece, middlepiece , secondpiece);


    char history[5000];
    char times[200];
    char notifica[200];
    char jarvistesto[5000];
    char userjson[3000];
    char jarvisjson[5000];

    while ((nread = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {    // Legge da stdin (che riceverà l’audio in tempo reale)

       if (vosk_recognizer_accept_waveform(recognizer, buffer, nread)) { 

            printf("%s\n", vosk_recognizer_result(recognizer));

        } else {

          printf("%s\n", vosk_recognizer_partial_result(recognizer));
        if (strstr( vosk_recognizer_partial_result(recognizer) , "jarvis") || strstr( vosk_recognizer_partial_result(recognizer) , "darwin")){

          json_error_t error;
          json_t *middlepiece = json_loads(vosk_recognizer_partial_result(recognizer), 0 , &error );
          const char *testo = json_string_value(json_object_get(middlepiece, "partial"));
  
          snprintf(userjson, sizeof(userjson), "{\"role\": \"user\", \"content\": \"%s , rispondi al seguente messaggio : %s\"}",jarvisnoncapisceuncazzo1 , testo);
          snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ", userjson);
          system(full_command1);

          system("curl -s https://api.groq.com/openai/v1/chat/completions \
          -H \"Authorization: Bearer \" \
          -H \"Content-Type: application/json\" \
          -d \"{ \
          \\\"model\\\": \\\"meta-llama/llama-4-scout-17b-16e-instruct\\\", \
          \\\"messages\\\": $(cat history.json) \
          }\" | jq -r '.choices[0].message.content' > output.txt && cat output.txt ");

          system("jq -r '.risposta' output.txt > risposta.txt");
          system("jq -r '.azione' output.txt > azione.txt && sleep 0.02");

          FILE *response = fopen("risposta.txt", "r");  
          while(fgets(jarvistesto , sizeof(jarvistesto) , response)){
            speak(jarvistesto);
          }
          fclose(response);

          FILE *action = fopen("azione.txt", "r");  
          while(fgets(azionetesto , sizeof(azionetesto) , action)){
          }
          fclose(action);
          printf("%s", azionetesto);
          
          snprintf(jarvisjson, sizeof(jarvisjson), "{\"role\": \"assistant\", \"content\": \"%s\"}"  , jarvistesto);
          snprintf(full_command1, sizeof(full_command1), "jq '. += [%s]' history.json > tmp && mv tmp history.json ", jarvisjson);
          system(full_command1);


          if (strstr( azionetesto , "musica")) system("mpv ~/Downloads/musica/*mp3 &");
          if (strstr( azionetesto , "musica1")) system("ssh gioele@192.168.1.113 'mpv ~/Downloads/musica/*mp3' &");
          if (strstr( azionetesto, "spegnimento1"))system("ssh -v gioele@192.168.1.113 ; ssh gioele@192.168.1.113 sudo /usr/bin/shutdown now");;
          if (strstr( azionetesto, "spegnimento")) break;
          if (strstr( azionetesto, "aggiornamento memoria")) system("jq -r '.aggiornamento' output.txt | tr -d '\n' >> memoria.txt");

          if (strstr( azionetesto, "invio notifica")){

            system("jq -r '.tempo' output.txt > notify.txt && jq -r '.notifica' output.txt >> notify.txt");
            FILE *notifics = fopen("notify.txt", "r");  
            for(int i = 0; i < 2 ; i++){
             if (i == 0){
              fgets(times , sizeof(times) , notifics);
              printf("TEMPO : %s", times);
             }else{
              fgets(notifica , sizeof(notifica) , notifics);
              printf("CORPO DELLA NOTIFICA : %s\n", notifica);
             }
            }
            fclose(action);
            strip_newline(times);
            strip_newline(notifica);
            snprintf(telegrammessage, sizeof(telegrammessage),"curl -s -X POST https://api.telegram.org/botTOKEN-d chat_id=CHATID -d text=\"MESSAGGIO INVIATO TRAMITE JARVIS : %s\" " , notifica);           
            printf("COMANDO : %s", telegrammessage);
            snprintf(full_command1, sizeof(full_command1), "sleep %s && notify-send \"JARVIS\" \"%s\" && mpv ~/Downloads/notification-2-269292.mp3 && %s & ", times, notifica, telegrammessage);           
            printf("COMANDO : %s", full_command1);
            system(full_command1);
        
          } 

/*
 
"risposta": "Tra 10 secondi ti ricorderò di andare a fare la spesa",
"azione": "invio notifica",
"tempo": 10,
"notifica": "andare a fare la spesa"

*/

          if (strstr( azionetesto , "meteo")) system("curl https://wttr.in/Bologna && sleep 5.0 ");
          vosk_recognizer_reset(recognizer);


        }

        }
    }

    printf("%s\n", vosk_recognizer_final_result(recognizer));

    vosk_recognizer_free(recognizer);
    vosk_model_free(model);
    return 0;
}


