
import java.io.*;
import java.util.*;

public class Reclame extends Task {
    Integer numberOfFamilies;

    Integer numberOfRelations;

    Integer extendedFamilySize;

    Integer[][] relations;

    List<ArrayList<Integer>> variablesCodification;

    boolean oracleAnswer;

    Integer variablesNumber;

    List<Integer> variables;

    List<Integer> decodifiedVariables;

    @Override
    public void solve() throws IOException, InterruptedException {
        readProblemData();
        formulateOracleQuestion();
        askOracle();
        decipherOracleAnswer();
        writeAnswer();
    }

    @Override
    public void readProblemData() throws IOException {
        BufferedReader input = new BufferedReader(new FileReader(inFilename));

        String[] firstLineElems = input.readLine().split("\\s");

        numberOfFamilies = Integer.parseInt(firstLineElems[0]);

        numberOfRelations = Integer.parseInt(firstLineElems[1]);

        extendedFamilySize = Integer.parseInt(firstLineElems[2]);

        relations = new Integer[numberOfFamilies][numberOfFamilies];

        // initialize each family relation with 0 first
        for (int i = 0; i < numberOfFamilies; i++) {
            for (int j = 0; j < numberOfFamilies; j++) {
                relations[i][j] = 0;
            }
        }

        // if 2 families are in relation, we will mark it with a '1' in the relations matrix
        for (int i = 0; i < numberOfRelations; i++) {
            String[] currentLine = input.readLine().split("\\s");

            int firstFamily = Integer.parseInt(currentLine[0]);
            int secondFamily = Integer.parseInt(currentLine[1]);

            relations[firstFamily - 1][secondFamily - 1] = 1;
            relations[secondFamily - 1][firstFamily - 1] = 1;
        }

        input.close();
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
        int variablesNo = numberOfFamilies * extendedFamilySize;

        int currentVariable = 1;

        variablesCodification = new ArrayList<ArrayList<Integer>>(variablesNo);

        // we will use a list so we can avoid adding duplicate clauses
        List<String> clauses = new ArrayList<String>();

        // first set of clauses - each family can be the ith one from the extended family
        for (int i = 1; i <= extendedFamilySize; i++) {
            String clauseToBeAdded = "";

            for (int j = 1; j <= numberOfFamilies; j++) {
                // codify the current family
                ArrayList<Integer> familyCodified = new ArrayList<Integer>(Arrays.asList(i, j));

                variablesCodification.add(currentVariable - 1, familyCodified);

                // compose the clause
                clauseToBeAdded += currentVariable + " ";

                currentVariable++;
            }
            // save the clause
            clauseToBeAdded += "0\n";
            clauses.add(clauseToBeAdded);
        }

        // the restriction clauses
        for (int i = 1; i <= variablesNo; i++) {
            int firstFamilyIndex = variablesCodification.get(i - 1).get(0);
            int firstFamilyNumber = variablesCodification.get(i - 1).get(1);

            for (int j = 1; j <= variablesNo; j++) {
                if (i != j) {
                    int secondFamilyIndex = variablesCodification.get(j - 1).get(0);
                    int secondFamilyNumber = variablesCodification.get(j - 1).get(1);

                    int var1 = i, var2 = j;

                    if (relations[firstFamilyNumber - 1][secondFamilyNumber - 1].equals(0)
                            && relations[secondFamilyNumber - 1][firstFamilyNumber - 1].equals(0)
                            && (firstFamilyNumber != secondFamilyNumber)) {
                        // 2 families that don't have a relation between themselves
                        // can't be part of the extended family
                        var1 = -i;
                        var2 = -j;

                        clauses.add(var1 + " " + var2 + " 0\n");
                    } else if ((((firstFamilyNumber == secondFamilyNumber)
                            && (firstFamilyIndex != secondFamilyIndex))
                            || ((firstFamilyNumber != secondFamilyNumber)
                            && (firstFamilyIndex == secondFamilyIndex)))) {
                        // a family can't be both the ith and the jth one from a extended family or
                        // 2 distinct families can't be both the ith one from the extended family
                        var1 = -i;
                        var2 = -j;

                        clauses.add(var1 + " " + var2 + " 0\n");
                    } else {
                        continue;
                    }
                }
            }
        }

        FileWriter writer = new FileWriter(oracleInFilename);

        writer.write("p cnf " + variablesNo + " " + clauses.size() + "\n");

        // write each clause
        for (String clauseIterator : clauses) {
            writer.write(clauseIterator);
        }

        writer.flush();
        writer.close();
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
        BufferedReader solution = new BufferedReader(new FileReader(oracleOutFilename));

        oracleAnswer = Boolean.parseBoolean(solution.readLine().split("\\s")[0]);

        if (oracleAnswer) {
            variablesNumber = Integer.parseInt(solution.readLine().split("\\s")[0]);

            String[] variablesInput = solution.readLine().split("\\s");

            // the initial answer which contains each literal value
            variables = new ArrayList<Integer>();

            for (int i = 0; i < variablesNumber; i++) {
                variables.add(i, Integer.parseInt(variablesInput[i]));
            }

            // decoding the oracleAnswer
            decodifiedVariables = new ArrayList<Integer>();

            for (int i = 0; i < variablesNumber; i ++) {
                if (variables.get(i) > 0) {
                    decodifiedVariables.add(variablesCodification.get(i).get(1));
                }
            }
        }

        solution.close();
    }

    @Override
    public void writeAnswer() throws IOException {
        FileWriter out = new FileWriter(outFilename);

        if (oracleAnswer) {
            out.write("True \n");

            // write each family number from the extended family
            for (int i = 0; i < decodifiedVariables.size(); i ++) {
                out.write(decodifiedVariables.get(i) + " ");
            }

            out.flush();
            out.close();
        } else {
            out.write("False \n");

            out.flush();
            out.close();
        }
    }
}