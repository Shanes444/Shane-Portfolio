//Shane Stevens & Milo Tomlinson Part A
//Takes an NFA file and stores it

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.ArrayList;

public class NFA2DFA{
    public static void main(String args[]){
        if(args.length != 1){
            System.out.println("Must have the proper amount of arguments");
            System.out.println("Expected call: nfa textfile");
            System.exit(-1);
        }
        System.out.println("temp");
        
        try {
            File nfaFile = new File(args[0]);
            Scanner scan = new Scanner(nfaFile);
            String str;
            int lineNum = 0;
            int charNum;
            String number;
            int numQ = 0;
            ArrayList<Character> sigmaList = new ArrayList<Character>();
            char[] sigma;
            boolean[][][] pathlist;
            int stateNum;
            int columnNum;
            boolean[] isAccepting;
            int initial;

            //line 1 being read
            str = scan.nextLine();
            number = "";
            lineNum++;
            charNum = 0;
            while(str.charAt(charNum) != ' '){
                charNum++;
            }
            charNum ++;
            while(charNum < str.length()){
                number += str.charAt(charNum);
                charNum++;
            }
            numQ = Integer.parseInt(number);

            //line 2 being read
            str = scan.nextLine();
            number = "";
            lineNum++;
            charNum = 0;
            while(str.charAt(charNum) != ' '){
                charNum++;
            }
            charNum ++;
            while(charNum < str.length()){
                if(str.charAt(charNum) != ' '){
                    sigmaList.add(str.charAt(charNum));   
                }
                charNum++;
            }
            sigma = new char[sigmaList.size()];
            for(int i = 0; i < sigma.length; i++){
                sigma[i] = (char)sigmaList.get(i);
            }
            pathlist = new boolean[numQ][sigma.length+1][numQ];
            isAccepting = new boolean[numQ];
            str = scan.nextLine();
            lineNum++;
            str = scan.nextLine();
            lineNum++;
            //lines 4 through 4 + numQ being read
            
            while(lineNum >= 4 && lineNum < 4+numQ){
                number = "";
                
                charNum = 0;
                stateNum = lineNum-4;
                columnNum = 0;
                while(str.charAt(charNum) != '{'){
                    charNum++;
                }
                charNum++;
                while(charNum < str.length()){      
                    
                    if(str.charAt(charNum) == ',' || str.charAt(charNum) == '}'){
                        if(number != ""){
                            pathlist[stateNum][columnNum][Integer.parseInt(number)] = true;
                            number = "";     
                        }          
                    }
                    else if(str.charAt(charNum) == '{'){
                        columnNum++;
                    }
                    else if(str.charAt(charNum) != ' '){
                        number += str.charAt(charNum);
                    }
                    charNum++;           
                }
            //     System.out.println();
            //         for(int i = 0; i <pathlist[stateNum].length; i++){              
            //             for(int j = 0; j < pathlist[stateNum][i].length; j++){
            //                 System.out.print(pathlist[stateNum][i][j] + " ");
            //             }
            //             System.out.println();
            //         }
                str = scan.nextLine();
                lineNum++;
            }
            str = scan.nextLine();
            lineNum++;

            //line 5 + numQ being read
            charNum = 0;
            while(str.charAt(charNum) != ':'){
                charNum++;
            }
            charNum++;
            while(charNum < str.length()){
                if(str.charAt(charNum) != ' '){
                    number += str.charAt(charNum);
                }
                charNum ++;
            }
            initial = Integer.parseInt(number);
            number = "";
            
            str = scan.nextLine();
            lineNum ++;
            //line 6 + numQ being read
            charNum = 0;
            while(str.charAt(charNum) != ':'){
                charNum ++;
            }
            charNum ++;
            
            while(charNum < str.length()){
                if(str.charAt(charNum) == ','){
                    isAccepting[Integer.parseInt(number)] = true;
                    number = "";
                }
                else if(str.charAt(charNum) != ' '){
                    number += str.charAt(charNum);
                }
                charNum++;
            }
            if(number != ""){
                isAccepting[Integer.parseInt(number)] = true;
            }
            // System.out.println(initial);
            // for(int i = 0; i < isAccepting.length; i++){
            //     System.out.print(isAccepting[i] + " ");
            // }

            //creation of nfa
            NFA nfaGraph = new NFA(numQ, initial, sigma, pathlist, isAccepting);
            DFA dfaGraph = convertNFA.convertNFAtoDFA(nfaGraph);
            System.out.println(dfaGraph.toString());
            
            DFA minDfa = minimizeDFA.minimize(dfaGraph);
            System.out.println();
            System.out.println(minDfa.toString());

            str = scan.nextLine();
            str = scan.nextLine();
            // for(int i = 0; i < nfaGraph.states.length; i++){
            //     System.out.print(nfaGraph.states[i].isAccepting);   
            // }
            // System.out.println();
            // for(int i = 0; i < dfaGraph.states.length; i++){
            //     System.out.print(dfaGraph.states[i].isAccepting);
            // }
            // System.out.println();

            int omegaNum = 1;
            while(scan.hasNext()){
                str = scan.nextLine();
                if(dfaGraph.toState(str) == true){
                    System.out.print("Yes  ");
                }
                else{
                    System.out.print("No   ");
                }
                omegaNum++;
                if(omegaNum == 16){
                    System.out.println();
                }

            }

            System.out.println();

            scan.close();         
        }
        catch(FileNotFoundException e){
            System.out.println("Invalid File");
            e.printStackTrace();
        }   
    }
}