cmake_minimum_required(VERSION 3.12)
project(E01 C)

set(CMAKE_C_STANDARD 99)

add_executable(E01 main.c data.h data.c titolo.c titolo.h BSTquotazioniGiornaliere.c BSTquotazioniGiornaliere.h quotazioneGiornaliera.c quotazioneGiornaliera.h ListTitoli.c ListTitoli.h)