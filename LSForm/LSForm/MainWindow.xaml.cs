using System;
using System.Globalization;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Xml;
using System.IO;

namespace LSForm
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        /*
         * Init = 0,
         * Iters = 1,
         * Width0 = 2,
         * Width1 = 3,
         * Angle = 4,
         * Scaling = 5
         */
        private bool[] mainFlags = new bool[6] { true, true, true, true, true, true };
        private List<bool> ruleFlags = new List<bool>();
        private ConsoleColor defaultFore;

        public MainWindow()
        {
            CultureInfo.CurrentCulture = CultureInfo.InvariantCulture;
            ruleFlags.Add(true);
            ruleFlags.Add(true);
            defaultFore = Console.ForegroundColor;
            InitializeComponent();
        }

        public float Width0 { get; set; }
        public float Width1 { get; set; }
        public int Iters { get; set; }
        public float Angle { get; set; }
        public float Scaling { get; set; }

        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            Grid grid = new Grid();
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.ColumnDefinitions.Add(new ColumnDefinition());
            grid.ColumnDefinitions.Add(new ColumnDefinition { Width = new GridLength(24.0) });
            grid.Margin = new Thickness(0.0, 0.0, 0.0, 8.0);
            TextBox boxR = new TextBox();
            boxR.MaxLength = 1;
            boxR.Text = "R";
            boxR.TextChanged += BoxR_TextChanged;
            Grid.SetColumn(boxR, 0);
            TextBox boxE = new TextBox();
            boxE.Margin = new Thickness(8.0, 0.0, 8.0, 0.0);
            boxE.Text = $"Rule #{StackRules.Children.Count}";
            Grid.SetColumn(boxE, 1);
            Button button = new Button();
            button.Content = "-";
            button.Click += ButtonRemove_Click;
            Grid.SetColumn(button, 2);
            grid.Children.Add(boxR);
            grid.Children.Add(boxE);
            grid.Children.Add(button);
            StackRules.Children.Insert(StackRules.Children.Count - 1, grid);
            ruleFlags.Add(true);
        }

        private void ButtonRemove_Click(object sender, RoutedEventArgs e)
        {
            if (StackRules.Children.Count > 2)
            {
                Grid grid = (sender as Button).Parent as Grid;
                ruleFlags.RemoveAt(StackRules.Children.IndexOf(grid));
                StackRules.Children.Remove(grid);
            }
        }

        private void InitBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            string input = InitBox.Text;
            if (input.Length < 1)
            {
                InitBox.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[0] = false;
            }
            else
            {
                InitBox.Background = new SolidColorBrush(Colors.White);
                mainFlags[0] = true;
            }
        }

        private void BoxR_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox box = sender as TextBox;
            int index = StackRules.Children.IndexOf(box.Parent as Grid);
            string input = box.Text;
            if (input.Length != 1)
            {
                box.Background = new SolidColorBrush(Colors.Pink);
                ruleFlags[index] = false;
            }
            else
            {
                box.Background = new SolidColorBrush(Colors.White);
                ruleFlags[index] = true;
            }
        }

        private void BoxIter_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxIter.Text;
                Iters = int.Parse(input);
                if (Iters < 0)
                    throw new Exception();
                BoxIter.Background = new SolidColorBrush(Colors.White);
                mainFlags[1] = true;
            }
            catch
            {
                BoxIter.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[1] = false;
            }
        }

        private void BoxWidth0_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxWidth0.Text;
                Width0 = float.Parse(input);
                if (Width0 <= 0.0)
                    throw new Exception();
                BoxWidth0.Background = new SolidColorBrush(Colors.White);
                mainFlags[2] = true;
            }
            catch
            {
                BoxWidth0.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[2] = false;
            }
        }

        private void BoxWidth1_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = BoxWidth1.Text;
                Width1 = float.Parse(input);
                if (Width1 <= 0.0)
                    throw new Exception();
                BoxWidth1.Background = new SolidColorBrush(Colors.White);
                mainFlags[3] = true;
            }
            catch
            {
                BoxWidth1.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[3] = false;
            }
        }

        private void AngleBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = AngleBox.Text;
                Angle = float.Parse(input);
                AngleBox.Background = new SolidColorBrush(Colors.White);
                mainFlags[4] = true;
            }
            catch
            {
                AngleBox.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[4] = false;
            }
        }

        private void ScaleBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            try
            {
                string input = ScaleBox.Text;
                Scaling = float.Parse(input);
                if (Scaling <= 0.0)
                    throw new Exception();
                ScaleBox.Background = new SolidColorBrush(Colors.White);
                mainFlags[5] = true;
            }
            catch
            {
                ScaleBox.Background = new SolidColorBrush(Colors.Pink);
                mainFlags[5] = false;
            }
        }

        private void WriteInt(BinaryWriter writer, int value)
        {
            Console.Write($"{sizeof(int)} bytes : ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(value);
            Console.ForegroundColor = defaultFore;
            writer.Write(value);
        }

        private void WriteFloat(BinaryWriter writer, float value)
        {
            Console.Write($"{sizeof(float)} bytes : ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(value);
            Console.ForegroundColor = defaultFore;
            writer.Write(value);
        }

        private void WriteBytes(BinaryWriter writer, byte[] value)
        {
            Console.Write($"{value.Length} bytes : ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.Write("[");
            for (int i = 0; i < value.Length; ++i)
                if (i < value.Length - 1)
                    Console.Write($"{value[i]}, ");
                else
                    Console.WriteLine($"{value[i]}]");
            Console.ForegroundColor = defaultFore;
            writer.Write(value);
        }

        private void WriteString(BinaryWriter writer, string value)
        {
            byte[] array = Encoding.ASCII.GetBytes(value);
            Console.Write($"{array.Length} bytes : ");
            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine(value);
            Console.ForegroundColor = defaultFore;
            writer.Write(array);
        }

        private bool ValidationTest()
        {
            if (mainFlags[0] == false)
            {
                MessageBox.Show("Ошибка при заполнении инициализирующей строки: её длина равна нулю",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            if (mainFlags[1] == false)
            {
                MessageBox.Show("Ошибка при заполнении стартовой итерации: должно быть целое число 0 или выше",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            if (mainFlags[2] == false)
            {
                MessageBox.Show("Ошибка при заполнении толщины нулевой вложенности: должно быть число больше нуля",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            if (mainFlags[3] == false)
            {
                MessageBox.Show("Ошибка при заполнении толщины последней вложенности: должно быть число больше нуля",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            if (mainFlags[4] == false)
            {
                MessageBox.Show("Ошибка при заполнении угла поворота",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            if (mainFlags[5] == false)
            {
                MessageBox.Show("Ошибка при заполнении масштабирования:  должно быть число больше нуля",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                return false;
            }
            for (int i = 0; i < ruleFlags.Count; ++i)
                if (ruleFlags[i] == false)
                {
                    MessageBox.Show($"Ошибка при заполнении обозначения правила #{i + 1}: должен быть один символ",
                        "Ошибка", MessageBoxButton.OK, MessageBoxImage.Warning);
                    return false;
                }
            return true;
        }

        private void ButtonRender_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (!ValidationTest())
                    return;
                int rulesCount = StackRules.Children.Count - 1;
                using (BinaryWriter writer = new BinaryWriter(File.Open("input.bin", FileMode.Create)))
                {

                    Console.WriteLine("Generation of \"input.bin\"...");
                    WriteInt(writer, rulesCount);
                    WriteInt(writer, InitBox.Text.Length);
                    WriteString(writer, InitBox.Text);
                    for (int i = 0; i < rulesCount; ++i)
                    {
                        var grid = StackRules.Children[i] as Grid;
                        var boxR = grid.Children[0] as TextBox;
                        var boxE = grid.Children[1] as TextBox;
                        WriteString(writer, boxR.Text);
                        WriteInt(writer, boxE.Text.Length);
                        WriteString(writer, boxE.Text);
                    }
                    WriteInt(writer, Iters);
                    Color color0 = ColorPicker0.SelectedColor.Value;
                    Color color1 = ColorPicker1.SelectedColor.Value;
                    byte[] colorBytes0 = new byte[4] { color0.R, color0.G, color0.B, color0.A };
                    byte[] colorBytes1 = new byte[4] { color1.R, color1.G, color1.B, color1.A };
                    WriteBytes(writer, colorBytes0);
                    WriteBytes(writer, colorBytes1);
                    WriteFloat(writer, Width0);
                    WriteFloat(writer, Width1);
                    WriteFloat(writer, (float)(Angle * Math.PI / 180.0));
                    WriteFloat(writer, Scaling);
                    Console.WriteLine($"Total {writer.BaseStream.Length} bytes.");
                }
            }
            catch
            {
                MessageBox.Show("Ошибка при создании промежуточного файла", "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
