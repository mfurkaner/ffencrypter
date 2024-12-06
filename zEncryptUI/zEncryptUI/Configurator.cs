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
        public string seedfile = string.Empty;
        public List<string> seeds = new List<string>();
        public bool mangle = true;
        public int mangleDepth = 10;
        public bool binary = true;
        public bool check = true;

        public string infilepath = string.Empty;
        public string outfilepath = string.Empty;


        public const string CommandKey = "command";
        public const string IDKey = "id";
        public const string PassKey = "pass";
        public const string InFileKey = "filepath";
        public const string OutFileKey = "fileout";
        public const string SeedFileKey = "seedfile";
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

        public void SetSeedfile(string seedfile)
        {
            config.seedfile = seedfile;
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

        public void ResetConfig()
        {
            config = new zEncryptorConfiguration();
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

            if (config.seedfile != string.Empty)
                configStr += $"{zEncryptorConfiguration.SeedFileKey} = '{config.seedfile}'\n";
            else
            {
                foreach (string s in config.seeds)
                {
                    configStr += $"{zEncryptorConfiguration.SeedKey} = '{s}'\n";
                }
            }

            configStr += $"{zEncryptorConfiguration.InFileKey} = '{config.infilepath}'\n";
            configStr += $"{zEncryptorConfiguration.OutFileKey} = '{config.outfilepath}'\n";

            File.WriteAllText(filename, configStr);
        }


        public bool ReadFromFile(string filename)
        {
            try
            {
                var lines = File.ReadAllLines(filename);
                config = new zEncryptorConfiguration();

                foreach (var line in lines)
                {
                    if (line.StartsWith('#'))
                        continue;

                    if (line.StartsWith(zEncryptorConfiguration.CommandKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.command = com;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.IDKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.id = com;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.PassKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.pass = com;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.mangleKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.mangle = int.Parse(com) == 1;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.depthKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.mangleDepth = int.Parse(com);
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.checkKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.check = int.Parse(com) == 1;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.binKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Replace(" ", "");

                        config.binary = int.Parse(com) == 1;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.SeedFileKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Remove(0, com.IndexOf('\'') + 1);
                        com = com.Remove(com.IndexOf('\''));

                        config.seedfile = com;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.SeedKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Remove(0, com.IndexOf('\'') + 1);
                        com = com.Remove(com.IndexOf('\''));

                        config.seeds.Add(com);
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.InFileKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Remove(0, com.IndexOf('\'') + 1);
                        com = com.Remove(com.IndexOf('\''));

                        config.infilepath = com;
                    }
                    else if (line.StartsWith(zEncryptorConfiguration.OutFileKey))
                    {
                        var com = line.Remove(0, line.IndexOf('=') + 1);
                        com = com.Remove(0, com.IndexOf('\'') + 1);
                        com = com.Remove(com.IndexOf('\''));

                        config.outfilepath = com;
                    }
                }
            }
            catch (Exception e)
            {
                return false;
            }


            return true;
        }
    }
}
