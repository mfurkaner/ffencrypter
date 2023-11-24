using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace zEntryptUI
{
    public class zEncryptorConfiguration
    {

        public string command = string.Empty;
        public string id = string.Empty;
        public string pass = string.Empty;
        public List<string> seeds = new List<string>();
        public bool mangle = true;
        public int mangleDepth = 5;
        public bool binary = true;
        public bool check = false;

        public string infilepath = string.Empty;
        public string outfilepath = string.Empty;


        public const string CommandKey = "command";
        public const string IDKey = "id";
        public const string PassKey = "pass";
        public const string InFileKey = "filepath";
        public const string OutFileKey = "fileout";
        public const string SeedKey = "addseed";
        public const string mangleKey = "mangle";
        public const string binKey = "binfile";
        public const string checkKey = "check";
        public const string depthKey = "depth";
    }

    public class Configurator
    {
        private static Configurator? _instance = null;
        private zEncryptorConfiguration config = new zEncryptorConfiguration();

        private Configurator() { }

        public static Configurator GetInstance()
        {
            if (_instance == null)
            {
                _instance = new Configurator();
            }
            return _instance;
        }

        public void SetCommand(string command)
        {
            config.command = command;
        }

        public void SetID(string id)
        {
            config.id = id;
        }

        public void SetPass(string pass)
        {
            config.pass = pass;
        }

        public void SetSeeds(List<string> seeds)
        {
            config.seeds = seeds;
        }

        public void SetMangle(bool mangle)
        {
            config.mangle = mangle;
        }

        public void SetBinary(bool binary)
        {
            config.binary = binary;
        }

        public void SetCheck(bool check)
        {
            config.check = check;
        }

        public void SetMangleDepth(int depth)
        {
            config.mangleDepth = depth;
        }

        public void SetInFilepath(string infile)
        {
            config.infilepath = infile;
        }

        public void SetOutFilepath(string outfile)
        {
            config.outfilepath = outfile;
        }


        public void SaveConfig(string filename)
        {
            string configStr = string.Empty;

            configStr += $"{zEncryptorConfiguration.CommandKey} = {config.command}\n";
            configStr += $"{zEncryptorConfiguration.IDKey} = {config.id}\n";
            configStr += $"{zEncryptorConfiguration.PassKey} = {config.pass}\n";
            configStr += $"{zEncryptorConfiguration.mangleKey} = {(config.mangle ? 1: 0)}\n";
            configStr += $"{zEncryptorConfiguration.depthKey} = {config.mangleDepth} \n";
            configStr += $"{zEncryptorConfiguration.checkKey} = {(config.check ? 1 : 0)} \n";
            configStr += $"{zEncryptorConfiguration.binKey} = {(config.binary ? 1 : 0)} \n";

            foreach(string s in config.seeds)
            {
                configStr += $"{zEncryptorConfiguration.SeedKey} = '{s}'\n";
            }

            configStr += $"{zEncryptorConfiguration.InFileKey} = {config.infilepath}\n";
            configStr += $"{zEncryptorConfiguration.OutFileKey} = {config.outfilepath}\n";

            File.WriteAllText(filename, configStr);
        }

    }
}
