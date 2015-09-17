# huffman_code_zip
compress a file by using huffman code

파일 목록
PA_201024441.exe : 리눅스에서 컴파일된 실행파일
HuffmanCodeZip.cpp : 압축을 위한 HuffanCodeZip클래스와 main이 포함된 파일
BGM_temp_BitStream.h : 바이너리 코드 입출력을 위해 만든 클래스
이하 트리를 위한 template코드들

특이사항
확장 ascii까지 고려하여 256가지 기호에 대해 huffman code를 생성.
표준 출력의 정보엔 기본 ascii의 정보만 출력함.
허프만 코드를 vector<bool>, list<bool>로 표현.
압축파일의 헤더엔 원본 파일의 각 ascii기호의 빈도가 저장됨. unsigned long long(8byte)로 빈도를 표현.
따라서 헤더는 256*8byte.
헤더가 크기에 원본 파일의 크기가 작다면 압축률이 100%를 넘는 경우가 발생.


허프만 코드 트리 작성까진 문제없음. 실제 .zip파일을 출력할 때, padding문제를 해결하지 않음. 주의할 것.
